#pragma once
#include "window/window.h"

namespace DELIB
{
    class SDLWindow : public Window
    {
    public:
        ~SDLWindow();

        void Init() override;
        void Destroy() override;
        void PollEvents() override;
        bool ShouldClose() override;
        void SwapBuffers() override;
        void RequestOpenGL(bool enabled);

    private:
        bool         gl_requested      = false;
        bool         should_close      = false;
        bool         owns_video        = false;  // did *we* init SDL's video subsystem?
        bool         swap_error_logged = false;  // keep per-frame errors out of the log
        unsigned int window_id         = 0;      // SDL_WindowID, kept SDL-free in this header
    };
}
