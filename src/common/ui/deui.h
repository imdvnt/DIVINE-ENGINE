#pragma once 
#include <delog.hpp>

namespace DELIB
{
    class DEUI
    {
    public:
        DEUI() {Logger::Info("Creating DEUI...");};
        ~DEUI() {Logger::Info("Destroying DEUI...");};
        void Init(void* window) {};
        void Render(void* window) {};
        void Shutdown() {};
    };
}