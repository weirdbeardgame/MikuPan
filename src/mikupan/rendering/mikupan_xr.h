#ifndef MIKUPAN_XR_H
#define MIKUPAN_XR_H
#include <openxr/openxr.h>
#include "SDL3/SDL_gpu.h"
#include "mikupan/mikupan_basictypes.h"
#include "mikupan/mikupan_types.h"


#define XR_CHECK(result, msg)                                                  \
    do                                                                         \
    {                                                                          \
        if (XR_FAILED(result))                                                 \
        {                                                                      \
            info_log("OpenXR Error: %s (result=%d)", msg, (int) (result));     \
            return false;                                                      \
        }                                                                      \
    }                                                                          \
    while (0)
#define XR_CHECK_QUIT(result, msg)                                             \
    do                                                                         \
    {                                                                          \
        if (XR_FAILED(result))                                                 \
        {                                                                      \
            info_log("OpenXR Error: %s (result=%d)", msg, (int) (result));     \
            quit(2);                                                           \
            return;                                                            \
        }                                                                      \
    }                                                                          \
    while (0)


/* Swapchain state */
typedef struct {
    XrSwapchain swapchain;
    SDL_GPUTexture **images;
    SDL_GPUTexture *depth_texture;  /* Local depth buffer for z-ordering */
    XrExtent2Di size;
    SDL_GPUTextureFormat format;
    Uint32 image_count;
} VRSwapchain;


/* ========================================================================
 * OpenXR Function Pointers (loaded dynamically)
 * ======================================================================== */

static PFN_xrGetInstanceProcAddr pfn_xrGetInstanceProcAddr = NULL;
static PFN_xrEnumerateViewConfigurationViews
    pfn_xrEnumerateViewConfigurationViews = NULL;
static PFN_xrEnumerateSwapchainImages pfn_xrEnumerateSwapchainImages = NULL;
static PFN_xrCreateReferenceSpace pfn_xrCreateReferenceSpace = NULL;
static PFN_xrDestroySpace pfn_xrDestroySpace = NULL;
static PFN_xrDestroySession pfn_xrDestroySession = NULL;
static PFN_xrDestroyInstance pfn_xrDestroyInstance = NULL;
static PFN_xrPollEvent pfn_xrPollEvent = NULL;
static PFN_xrBeginSession pfn_xrBeginSession = NULL;
static PFN_xrEndSession pfn_xrEndSession = NULL;
static PFN_xrWaitFrame pfn_xrWaitFrame = NULL;
static PFN_xrBeginFrame pfn_xrBeginFrame = NULL;
static PFN_xrEndFrame pfn_xrEndFrame = NULL;
static PFN_xrLocateViews pfn_xrLocateViews = NULL;
static PFN_xrAcquireSwapchainImage pfn_xrAcquireSwapchainImage = NULL;
static PFN_xrWaitSwapchainImage pfn_xrWaitSwapchainImage = NULL;
static PFN_xrReleaseSwapchainImage pfn_xrReleaseSwapchainImage = NULL;

/* OpenXR state */
static XrInstance xr_instance = XR_NULL_HANDLE;
static XrSystemId xr_system_id = XR_NULL_SYSTEM_ID;
static XrSession xr_session = XR_NULL_HANDLE;
static XrSpace xr_local_space = XR_NULL_HANDLE;

static bool xr_session_running = false;
static bool xr_should_quit = false;

static VRSwapchain *vr_swapchains = NULL;
static XrView *xr_views = NULL;
static Uint32 view_count = 0;


int MikuPan_XrInit();



#endif