#include "opengl_renderer.h"

#include <glad/glad.h>


namespace DELIB
{
    OpenGLRenderer::OpenGLRenderer(Window* window)
    {
        this->window = window;
        Init();
    }
    void OpenGLRenderer::Init()
    {
        glEnable(GL_DEPTH_TEST);
    }
    void OpenGLRenderer::ClearScreen(float r, float g, float b, float a)
    {
        glClearColor(r,g,b,a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void OpenGLRenderer::Destroy()
    {

    }

    void OpenGLRenderer::RenderMesh(const Mesh3D& mesh, const Camera& camera, const Shader& shader)
    {
        if (shader.program_id == 0)
        {
            Logger::Error("Shader program is not initialized. Cannot render mesh.");
            return;
        }

        shader.Bind();
        shader.SetUniformMat4("view", camera.GetViewMatrix());
        shader.SetUniformMat4("projection", camera.GetProjectionMatrix());

        for (const Triangle3D& triangle : mesh)
        {
            // Set vertex positions
            shader.SetUniformVec3("v0", triangle.vertices[0]);
            shader.SetUniformVec3("v1", triangle.vertices[1]);
            shader.SetUniformVec3("v2", triangle.vertices[2]);

            // Set vertex normals
            shader.SetUniformVec3("n0", triangle.normals[0]);
            shader.SetUniformVec3("n1", triangle.normals[1]);
            shader.SetUniformVec3("n2", triangle.normals[2]);

            // Set vertex UVs
            shader.SetUniformVec2("uv0", triangle.uvs[0]);
            shader.SetUniformVec2("uv1", triangle.uvs[1]);
            shader.SetUniformVec2("uv2", triangle.uvs[2]);

            // Draw the triangle
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }
    
}