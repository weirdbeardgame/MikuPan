#include "mikupan_xr.h"
#include "SDL3/SDL_openxr.h"
#include "SDL3/SDL_video.h"

static SDL_GPUDevice* g_device_xr = NULL;
static SDL_GPUTextureFormat g_depth_format = SDL_GPU_TEXTUREFORMAT_D32_FLOAT;

static bool load_xr_functions(void)
{
    pfn_xrGetInstanceProcAddr =
        (PFN_xrGetInstanceProcAddr) SDL_OpenXR_GetXrGetInstanceProcAddr();
    if (!pfn_xrGetInstanceProcAddr)
    {
        SDL_Log("Failed to get xrGetInstanceProcAddr");
        return false;
    }

#define XR_LOAD(fn)                                                            \
    if (XR_FAILED(pfn_xrGetInstanceProcAddr(xr_instance, #fn,                  \
                                            (PFN_xrVoidFunction*) &pfn_##fn))) \
    {                                                                          \
        SDL_Log("Failed to load " #fn);                                        \
        return false;                                                          \
    }

    XR_LOAD(xrEnumerateViewConfigurationViews);
    XR_LOAD(xrEnumerateSwapchainImages);
    XR_LOAD(xrCreateReferenceSpace);
    XR_LOAD(xrDestroySpace);
    XR_LOAD(xrDestroySession);
    XR_LOAD(xrDestroyInstance);
    XR_LOAD(xrPollEvent);
    XR_LOAD(xrBeginSession);
    XR_LOAD(xrEndSession);
    XR_LOAD(xrWaitFrame);
    XR_LOAD(xrBeginFrame);
    XR_LOAD(xrEndFrame);
    XR_LOAD(xrLocateViews);
    XR_LOAD(xrAcquireSwapchainImage);
    XR_LOAD(xrWaitSwapchainImage);
    XR_LOAD(xrReleaseSwapchainImage);

#undef XR_LOAD

    SDL_Log("Loaded all XR functions successfully");
    return true;
}

static bool create_swapchains(void)
{
    XrResult result;

    /* Get view configuration */
    result = pfn_xrEnumerateViewConfigurationViews(
        xr_instance, xr_system_id, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, 0,
        &view_count, NULL);
    XR_CHECK(result, "Failed to enumerate view config views (count)");

    SDL_Log("View count: %" SDL_PRIu32, view_count);

    XrViewConfigurationView* view_configs =
        SDL_calloc(view_count, sizeof(XrViewConfigurationView));
    for (Uint32 i = 0; i < view_count; i++)
    {
        view_configs[i].type = XR_TYPE_VIEW_CONFIGURATION_VIEW;
    }

    result = pfn_xrEnumerateViewConfigurationViews(
        xr_instance, xr_system_id, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO,
        view_count, &view_count, view_configs);
    if (XR_FAILED(result))
    {
        SDL_free(view_configs);
        SDL_Log("Failed to enumerate view config views");
        return false;
    }

    /* Allocate swapchains and views */
    vr_swapchains = SDL_calloc(view_count, sizeof(VRSwapchain));
    xr_views = SDL_calloc(view_count, sizeof(XrView));

    /* Query available swapchain formats
     * Per PR #14837: format arrays are terminated with
     * SDL_GPU_TEXTUREFORMAT_INVALID */
    int num_formats = 0;
    SDL_GPUTextureFormat* formats =
        SDL_GetGPUXRSwapchainFormats(g_device_xr, xr_session, &num_formats);
    if (!formats || num_formats == 0)
    {
        SDL_Log("Failed to get XR swapchain formats");
        SDL_free(view_configs);
        return false;
    }

    /* Use first available format (typically sRGB)
     * Note: Could iterate with: while (formats[i] !=
     * SDL_GPU_TEXTUREFORMAT_INVALID) */
    SDL_GPUTextureFormat swapchain_format = formats[0];
    SDL_Log("Using swapchain format: %d (of %d available)", swapchain_format,
            num_formats);

    /* Log all available formats for debugging */
    for (int f = 0;
         f < num_formats && formats[f] != SDL_GPU_TEXTUREFORMAT_INVALID; f++)
    {
        SDL_Log("  Available format [%d]: %d", f, formats[f]);
    }
    SDL_free(formats);

    for (Uint32 i = 0; i < view_count; i++)
    {
        xr_views[i].type = XR_TYPE_VIEW;
        xr_views[i].pose.orientation.w = 1.0f;

        SDL_Log("Eye %" SDL_PRIu32 ": recommended %ux%u", i,
                (unsigned int) view_configs[i].recommendedImageRectWidth,
                (unsigned int) view_configs[i].recommendedImageRectHeight);

        /* Create swapchain using OpenXR's XrSwapchainCreateInfo */
        XrSwapchainCreateInfo swapchain_info = {XR_TYPE_SWAPCHAIN_CREATE_INFO};
        swapchain_info.usageFlags = XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT
                                    | XR_SWAPCHAIN_USAGE_SAMPLED_BIT;
        swapchain_info.format = 0; /* Ignored - SDL uses the format parameter */
        swapchain_info.sampleCount = 1;
        swapchain_info.width = view_configs[i].recommendedImageRectWidth;
        swapchain_info.height = view_configs[i].recommendedImageRectHeight;
        swapchain_info.faceCount = 1;
        swapchain_info.arraySize = 1;
        swapchain_info.mipCount = 1;

        result = SDL_CreateGPUXRSwapchain(
            g_device_xr, xr_session, &swapchain_info, swapchain_format,
            &vr_swapchains[i].swapchain, &vr_swapchains[i].images);

        vr_swapchains[i].format = swapchain_format;

        if (XR_FAILED(result))
        {
            SDL_Log("Failed to create swapchain %" SDL_PRIu32, i);
            SDL_free(view_configs);
            return false;
        }
        /* Get image count by enumerating swapchain images */
        result = pfn_xrEnumerateSwapchainImages(
            vr_swapchains[i].swapchain, 0, &vr_swapchains[i].image_count, NULL);
        if (XR_FAILED(result))
        {
            vr_swapchains[i].image_count = 3; /* Assume 3 if we can't query */
        }

        vr_swapchains[i].size.width = (int32_t) swapchain_info.width;
        vr_swapchains[i].size.height = (int32_t) swapchain_info.height;

        /* Create local depth texture for this eye
         * Per PR #14837: Depth buffers are "really recommended" for XR apps.
         * Using a local depth texture (not XR-managed) is the simplest approach
         * for proper z-ordering without requiring
         * XR_KHR_composition_layer_depth. */
        SDL_GPUTextureCreateInfo depth_info = {
            .type = SDL_GPU_TEXTURETYPE_2D,
            .format = g_depth_format,
            .width = swapchain_info.width,
            .height = swapchain_info.height,
            .layer_count_or_depth = 1,
            .num_levels = 1,
            .sample_count = SDL_GPU_SAMPLECOUNT_1,
            .usage = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET,
            .props = 0};
        vr_swapchains[i].depth_texture =
            SDL_CreateGPUTexture(g_device_xr, &depth_info);
        if (!vr_swapchains[i].depth_texture)
        {
            SDL_Log("Failed to create depth texture for eye %" SDL_PRIu32
                    ": %s",
                    i, SDL_GetError());
            SDL_free(view_configs);
            return false;
        }

        SDL_Log("Created swapchain %" SDL_PRIu32 ": %" SDL_PRIs32
                "x%" SDL_PRIs32 ", %" SDL_PRIu32 " images, with depth buffer",
                i, vr_swapchains[i].size.width, vr_swapchains[i].size.height,
                vr_swapchains[i].image_count);
    }

    SDL_free(view_configs);
}

static bool init_xr_session(void)
{
    XrResult result;

    /* Create session */
    XrSessionCreateInfo session_info = {XR_TYPE_SESSION_CREATE_INFO};
    result = SDL_CreateGPUXRSession(g_device_xr, &session_info, &xr_session);
    XR_CHECK(result, "Failed to create XR session");

    if (result != XR_SUCCESS)
    {
        info_log("XR Session creation failed: %d\n", result);
        return false;
    }

    /* Create reference space */
    XrReferenceSpaceCreateInfo space_info = {
        XR_TYPE_REFERENCE_SPACE_CREATE_INFO};
    space_info.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_LOCAL;
    space_info.poseInReferenceSpace.orientation.w =
        1.0f; /* Identity quaternion */

    result =
        pfn_xrCreateReferenceSpace(xr_session, &space_info, &xr_local_space);
    XR_CHECK(result, "Failed to create reference space");

    return true;
}

void MikuPan_HandleXrEvents(void)
{
    XrEventDataBuffer event_buffer = {XR_TYPE_EVENT_DATA_BUFFER};

    while (pfn_xrPollEvent(xr_instance, &event_buffer) == XR_SUCCESS)
    {
        switch (event_buffer.type)
        {
            case XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED:
            {
                XrEventDataSessionStateChanged* state_event =
                    (XrEventDataSessionStateChanged*) &event_buffer;

                SDL_Log("Session state changed: %d", state_event->state);

                switch (state_event->state)
                {
                    case XR_SESSION_STATE_READY:
                    {
                        XrSessionBeginInfo begin_info = {
                            XR_TYPE_SESSION_BEGIN_INFO};
                        begin_info.primaryViewConfigurationType =
                            XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO;

                        XrResult result =
                            pfn_xrBeginSession(xr_session, &begin_info);
                        if (XR_SUCCEEDED(result))
                        {
                            SDL_Log("XR Session begun!");
                            xr_session_running = true;

                            /* Create swapchains now that session is ready */
                            if (!create_swapchains())
                            {
                                SDL_Log("Failed to create swapchains");
                                xr_should_quit = true;
                            }
                        }
                        break;
                    }
                    case XR_SESSION_STATE_STOPPING:
                        pfn_xrEndSession(xr_session);
                        xr_session_running = false;
                        break;
                    case XR_SESSION_STATE_EXITING:
                    case XR_SESSION_STATE_LOSS_PENDING:
                        xr_should_quit = true;
                        break;
                    default:
                        break;
                }
                break;
            }
            case XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING:
                xr_should_quit = true;
                break;
            default:
                break;
        }

        event_buffer.type = XR_TYPE_EVENT_DATA_BUFFER;
    }
}

int MikuPan_XrInit()
{
    if (!SDL_OpenXR_LoadLibrary())
    {
        info_log("Load Library Failed: %s", SDL_GetError());
        return 0;
    }

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetBooleanProperty(
        props, SDL_PROP_GPU_DEVICE_CREATE_SHADERS_SPIRV_BOOLEAN, true);
    SDL_SetBooleanProperty(
        props, SDL_PROP_GPU_DEVICE_CREATE_SHADERS_DXIL_BOOLEAN, true);
    SDL_SetBooleanProperty(props, SDL_PROP_GPU_DEVICE_CREATE_DEBUGMODE_BOOLEAN,
                           true);
    /* Enable XR - SDL will create the OpenXR instance for us */
    SDL_SetBooleanProperty(props, SDL_PROP_GPU_DEVICE_CREATE_XR_ENABLE_BOOLEAN,
                           true);
    SDL_SetPointerProperty(
        props, SDL_PROP_GPU_DEVICE_CREATE_XR_INSTANCE_POINTER, &xr_instance);
    SDL_SetPointerProperty(
        props, SDL_PROP_GPU_DEVICE_CREATE_XR_SYSTEM_ID_POINTER, &xr_system_id);
    SDL_SetStringProperty(props,
                          SDL_PROP_GPU_DEVICE_CREATE_XR_APPLICATION_NAME_STRING,
                          "MikuPan");

    SDL_SetNumberProperty(
        props, SDL_PROP_GPU_DEVICE_CREATE_XR_APPLICATION_VERSION_NUMBER, 1);

    g_device_xr = SDL_CreateGPUDeviceWithProperties(props);
    SDL_DestroyProperties(props);

    if (g_device_xr == NULL)
    {
        info_log("Error creating XR device: %s", SDL_GetError());
        return 0;
    }

    if (!load_xr_functions())
    {
        info_log("Failed to load XR functions");
        return 0;
    }

    init_xr_session();

    return 1;
}