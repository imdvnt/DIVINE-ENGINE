#pragma once
#include <delog.hpp>
#include <string>

namespace DELIB
{
    class Window
    {
    public:
        Window(int width = 800, int height = 600, std::string title = "Divine Engine") {
            Logger::Info("Creating window...");
        }
        virtual ~Window(){
            Logger::Info("Destroying window...");
        }
        
        void* context = nullptr;
        int min_width = 320;
        int min_height = 240;
        int width = 800;
        int height = 600;
        std::string title = "Divine Engine";

        virtual void Init() = 0;
        virtual void Destroy() = 0;
        virtual void PollEvents() = 0;
        virtual bool ShouldClose() = 0;
        virtual void SwapBuffers() = 0;
    };
}
