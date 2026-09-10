#pragma once 
#include "renderer/renderer.h"
#include "common/object3d/object3d.h"
#include "common/shader/shader.h"
#include "common/camera/camera.h"

#include <unordered_map>
namespace DELIB
{
    class OpenGLRenderer : public Renderer
    {
        std::unordered_map<std::string, unsigned int> shader_programs;
        Shader* current_shader = nullptr;
    public:
        OpenGLRenderer(Window* window);
        void Init() override;
        void ClearScreen (float r, float g, float b, float a) override ;
        void RenderMesh(const Mesh3D& mesh, const Camera& camera, const Shader& shader) override;
        void Destroy() override;
    };
}