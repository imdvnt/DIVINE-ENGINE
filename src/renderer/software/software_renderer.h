#pragma once
#include "renderer/renderer.h"

namespace DELIB
{
    class SoftwareRenderer : public Renderer
    {
    public:
        virtual void Init(Window* window) = 0;
        virtual void Destroy() = 0;
    };
}
