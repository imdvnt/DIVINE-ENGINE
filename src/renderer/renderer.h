#pragma once
#include <delog.hpp>

namespace DELIB
{
    class Window;
    class Object3D;
    struct Camera;

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
        virtual void RenderObject(const Object3D& object, const Camera& camera) = 0;
        virtual void Destroy() = 0;
    };
}
