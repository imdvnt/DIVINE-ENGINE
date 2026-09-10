#pragma once

#include <chrono>
#include <algorithm>

namespace DELIB
{
    class Time final
    {
    public:
        Time() = delete;

        using clock      = std::chrono::high_resolution_clock;
        using seconds_f  = std::chrono::duration<float>;

        static void Reset()
        {
            start_time       = clock::now();
            elapsed_seconds  = 0.0f;
            delta_time       = 0.0f;
            unscaled_delta   = 0.0f;
            time_scale       = 1.0f;
        }

        static void Update(float max_delta)
        {
            const auto now      = clock::now();
            const auto elapsed  = std::chrono::duration_cast<seconds_f>(now - start_time).count();

            unscaled_delta = std::min(elapsed - elapsed_seconds, max_delta);
            delta_time     = unscaled_delta * time_scale;
            elapsed_seconds = elapsed;
        }

        // getters
        static float SinceStart()        { return elapsed_seconds; }
        static float Delta()             { return delta_time; }
        static float UnscaledDelta()     { return unscaled_delta; }
        static float Scale()             { return time_scale; }

        // setters
        static void SetScale(float scale)
        {
            time_scale = std::max(scale, 0.0f);
        }

    private:
        static inline clock::time_point start_time = clock::now();

        static inline float elapsed_seconds = 0.0f;
        static inline float delta_time      = 0.0f;
        static inline float unscaled_delta  = 0.0f;
        static inline float time_scale      = 1.0f;
    };
}
