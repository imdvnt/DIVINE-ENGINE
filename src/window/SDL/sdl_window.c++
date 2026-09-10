#include <SDL3/SDL.h>
#include "delib.h"
#include "sdl_window.h"

namespace DELIB
{
    namespace
    {
        inline SDL_Window* AsWindow(void* ctx)
        {
            return static_cast<SDL_Window*>(ctx);
        }
    }

    SDLWindow::~SDLWindow()
    {
        Destroy();
    }

    void SDLWindow::RequestOpenGL(bool enabled)
    {
        if (context)
        {
            Logger::Warn("RequestOpenGL() ignored: window already created.");
            return;
        }
        gl_requested = enabled;
    }

    void SDLWindow::Init()
    {
        Logger::Info("Initializing SDL window...");

        if (context)
        {
            Logger::Warn("Init() ignored: SDL window already initialized.");
            return;
        }

        // Only touch the video subsystem if nobody else brought it up, so that
        // Destroy() can shut down exactly what it started.
        if (!SDL_WasInit(SDL_INIT_VIDEO))
        {
            if (!SDL_Init(SDL_INIT_VIDEO))
            {
                Logger::Error("SDL_Init(SDL_INIT_VIDEO) failed: ", SDL_GetError());
                return;
            }
            owns_video = true;
        }

        if (!context && owns_video)
        {
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
            owns_video = false;
        }
    }

    void SDLWindow::Destroy()
    {
        if (context)
        {
            SDL_DestroyWindow(AsWindow(context));
            context   = nullptr;
            window_id = 0;
            Logger::Info("SDL window destroyed.");
        }

        if (owns_video)
        {
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
            owns_video = false;
        }

        should_close = true;
    }

    void SDLWindow::PollEvents()
    {
        if (!context)
            return;

        // SDL_PollEvent pumps the queue itself, so no separate SDL_PumpEvents().
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    should_close = true;
                    break;

                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    if (event.window.windowID == window_id)
                        should_close = true;
                    break;

                case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                    if (event.window.windowID == window_id)
                    {
                        width  = event.window.data1;
                        height = event.window.data2;
                    }
                    break;

                default:
                    break;
            }
        }
    }

    bool SDLWindow::ShouldClose()
    {
        // No window means there is nothing left to run: report "closed" so the
        // caller's frame loop exits instead of spinning on a dead window.
        return should_close || context == nullptr;
    }

    void SDLWindow::SwapBuffers()
    {
        // Without SDL_WINDOW_OPENGL there is no GL surface to swap. The
        // SDL_Renderer backends present through SDL_RenderPresent instead.
        if (!context || !gl_requested)
            return;

        if (!SDL_GL_SwapWindow(AsWindow(context)) && !swap_error_logged)
        {
            Logger::Error("SDL_GL_SwapWindow failed: ", SDL_GetError());
            swap_error_logged = true;
        }
    }
}
