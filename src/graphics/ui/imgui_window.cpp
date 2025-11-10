#include "imgui_window.h"

#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

void InitImGuiWindow(SDL_Window *window, SDL_Renderer *renderer)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void RenderImGuiWindow(SDL_Renderer* renderer)
{
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void NewFrameImGuiWindow()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void DrawImGuiWindow()
{
    // You can choose to make the window static or toggle it via a bool
    ImGui::Begin("Performance");

    // ImGui provides a ready-made function for FPS:
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    // You can also show frame time in ms:
    ImGui::Text("Frame time: %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);

    ImGui::End();
}

void ShutDownImGuiWindow()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void ProcessEventImGui(SDL_Event *event)
{
    ImGui_ImplSDL3_ProcessEvent(event);
}
