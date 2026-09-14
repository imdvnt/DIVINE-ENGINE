#include "gl_renderer.h"
#include "renderer/object3d.h"

#include <cstddef>

namespace DELIB
{
    GL_Renderer::GL_Renderer(Window* window)
    {
        this->window = window;
        Init();
    }

    void GL_Renderer::Init()
    {
        glEnable(GL_DEPTH_TEST);

        default_shader = new Shader();
        default_shader->name = "default";
        const char* vertex_shader_source = R"(
            #version 330 core
            layout(location = 0) in vec3 aPos;
            layout(location = 1) in vec3 aNormal;
            layout(location = 2) in vec2 aTexCoords;

            uniform mat4 view;
            uniform mat4 projection;
            uniform mat4 model;

            out vec3 FragPos;
            out vec3 Normal;
            out vec2 TexCoords;

            void main()
            {
                vec4 world_pos = model * vec4(aPos, 1.0);
                FragPos = world_pos.xyz;
                Normal = normalize(mat3(model) * aNormal);
                TexCoords = aTexCoords;
                gl_Position = projection * view * world_pos;
            }
        )";

        const char* fragment_shader_source = R"(
            #version 330 core
            out vec4 FragColor;

            in vec3 FragPos;
            in vec3 Normal;
            in vec2 TexCoords;

            void main()
            {
                FragColor = vec4(Normal * 0.5 + 0.5, 1.0);
            }
        )";

        default_shader->CreateFromSource(vertex_shader_source, fragment_shader_source);
        if (!default_shader->IsValid())
        {
            Logger::Error("Default shader failed to build; nothing will be rendered.");
        }

        // Layout вершин задаётся один раз и запоминается в VAO.
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    void GL_Renderer::ClearScreen(float r, float g, float b, float a)
    {
        glClearColor(r,g,b,a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GL_Renderer::Destroy()
    {
        if (default_shader)
        {
            delete default_shader;
            default_shader = nullptr;
        }
        current_shader = nullptr;

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        VAO = 0;
        VBO = 0;
    }

    void GL_Renderer::RenderObject(const Object3D& object, const Camera& camera)
    {
        if (object.model.empty())
        {
            Logger::Warn("Object \"", object.name, "\" does not have a model assigned. Skipping render.");
            return;
        }

        // Отсутствие своего шейдера — штатный случай, рисуем дефолтным.
        current_shader = object.shader ? object.shader : default_shader;
        if (!current_shader || !current_shader->IsValid())
        {
            return;
        }

        current_shader->Bind();
        current_shader->SetUniformMat4("view", camera.GetViewMatrix());
        current_shader->SetUniformMat4("projection", camera.GetProjectionMatrix());
        current_shader->SetUniformMat4("model", object.transform.GetModelMatrix());

        if (object.material)
        {
            if (object.material->diffuse_texture)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, object.material->diffuse_texture->id);
            }
            if (object.material->specular_texture)
            {
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, object.material->specular_texture->id);
            }
        }

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        for (const Mesh3D& mesh : object.model)
        {
            if (mesh.empty())
            {
                continue;
            }

            vertex_scratch.clear();
            vertex_scratch.reserve(mesh.size() * 3);
            for (const Triangle3D& triangle : mesh)
            {
                for (int i = 0; i < 3; ++i)
                {
                    vertex_scratch.push_back({ triangle.vertices[i], triangle.normals[i], triangle.uvs[i] });
                }
            }

            // Перезаливка каждый кадр; кеш VBO на меш — следующий шаг.
            glBufferData(GL_ARRAY_BUFFER,
                         static_cast<GLsizeiptr>(vertex_scratch.size() * sizeof(Vertex)),
                         vertex_scratch.data(),
                         GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertex_scratch.size()));
        }

        glBindVertexArray(0);
    }
    
}
