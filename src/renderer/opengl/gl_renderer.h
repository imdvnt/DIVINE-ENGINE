#pragma once 

#include "renderer/camera.h"
#include "renderer/renderer.h"
#include "renderer/shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

namespace DELIB
{
    class GL_Renderer : public Renderer
    {
        // Формат вершины в VBO: Triangle3D хранит данные раздельно (SoA),
        // перед отрисовкой они распаковываются в этот interleaved-вид.
        struct Vertex
        {
            glm::vec3 position;
            glm::vec3 normal;
            glm::vec2 uv;
        };

        Shader* current_shader = nullptr;
        Shader* default_shader = nullptr;
        std::vector<Vertex> vertex_scratch;

        GLuint VAO = 0;
        GLuint VBO = 0;

    public:
        GL_Renderer(Window* window);
        void Init() override;
        void ClearScreen (float r, float g, float b, float a) override ;
        void RenderObject(const Object3D& object, const Camera& camera) override;
        void Destroy() override;
    };
}
