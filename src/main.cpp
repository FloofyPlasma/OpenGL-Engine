#include <cstdio>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_opengl.h>
#include <cstdlib>

int main(int argc, char const *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        printf("Error during SDL_Init(): %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

// TODO: Make this platform independent if possible...
#ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_Window *Window = SDL_CreateWindow("OpenGL Window", 1280, 720, SDL_WINDOW_OPENGL);
    if (Window == nullptr)
    {
        printf("Error during SDL_CreateWindow(): %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_GLContext Context = SDL_GL_CreateContext(Window);
    if (Context == nullptr)
    {
        printf("Error during SDL_GL_CreateContext(): %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_GL_MakeCurrent(Window, Context);
    SDL_GL_SetSwapInterval(1); // Vsync
    SDL_ShowWindow(Window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &IO = ImGui::GetIO();
    (void)IO;
    IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOpenGL(Window, Context);
    ImGui_ImplOpenGL3_Init("#version 410");

    bool ShouldQuit = false;

    bool ShowDemoWindow = true;

    while (!ShouldQuit)
    {
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            ShowDemoWindow = true;

            ImGui_ImplSDL3_ProcessEvent(&Event);

            if (Event.type == SDL_EVENT_QUIT)
            {
                ShouldQuit = true;
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(&ShowDemoWindow);
        ImGui::Render();
        glViewport(0, 0, static_cast<int>(IO.DisplaySize.x), static_cast<int>(IO.DisplaySize.y));
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(Window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DestroyContext(Context);
    SDL_DestroyWindow(Window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
