#pragma once
#include <delog.hpp>

#include "common/triangle3d/triangle3d.h"

namespace DELIB
{
    class Window;
    struct Camera;
    struct Shader;
    
    class Renderer
    {
    public:
        Renderer()
        {

        };
        Renderer(Window* window) : window(window) {
            Logger::Info("Creating renderer...");
        };
        virtual ~Renderer() {
            Logger::Info("Destroying renderer...");
        };
        Window* window = nullptr;
        virtual void Init() = 0;
        virtual void ClearScreen (float r, float g, float b, float a) = 0;
        virtual void RenderMesh(const Mesh3D& mesh, const Camera& camera, const Shader& shader) = 0;
        virtual void Destroy() = 0;
    };
}
