#pragma once
#include "window/window.h"

namespace DELIB
{
    class GLFWWindow : public Window
    {
    public:
        GLFWWindow(int width = 800, int height = 600, std::string title = "Divine Engine")
        {
            Init();
            this->width = width;
            this->height = height;
            this->title = title;
        };
        ~GLFWWindow()
        {
            Destroy();
        };
        void Init() override;
        void Destroy() override;
        void PollEvents() override;
        bool ShouldClose() override;
        void SwapBuffers() override;
    };
}