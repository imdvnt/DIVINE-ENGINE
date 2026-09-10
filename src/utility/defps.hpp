#pragma once

#ifdef _WIN32
    #include <windows.h>
#endif

#include <thread>
#include <chrono>

#include "detime.hpp"

namespace DELIB
{
    inline int& TargetFPS(int max_fps) {
        static int fps = max_fps;
        return fps;
    }

    inline double FPS() {
        float d = Time::UnscaledDelta();
        return d > 0.f ? 1.0 / d : 0.0;
    }

    inline void LimitFPS() {
        using clock = std::chrono::steady_clock;
        static clock::time_point start = clock::now();

        #ifdef _WIN32
            timeBeginPeriod(1);
        #endif

        const int target = TargetFPS();
        const double frame_time = target > 0 ? 1.0 / target : 0.0;
        const double elapsed    = std::chrono::duration<double>(clock::now() - start).count();
        const double left       = frame_time - elapsed;

        if (left > 0.0001) {
            std::this_thread::sleep_for(std::chrono::duration<double>(left * 0.5));
            while (std::chrono::duration<double>(clock::now() - start).count() < frame_time)
                std::this_thread::yield();
        }

        start = clock::now();
    }
}
