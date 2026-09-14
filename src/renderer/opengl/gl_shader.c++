#include "gl_shader.h"

#include <defile.hpp>
#include <delog.hpp>
#include <glad/glad.h>

namespace DELIB
{
    namespace
    {
        // Компилирует один шейдер; при ошибке пишет лог драйвера и возвращает 0.
        unsigned int CompileStage(GLenum type, const std::string& source, const char* stage_name)
        {
            unsigned int shader = glCreateShader(type);
            const char* src = source.c_str();
            glShaderSource(shader, 1, &src, nullptr);
            glCompileShader(shader);

            int ok = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
            if (!ok)
            {
                char info[1024];
                glGetShaderInfoLog(shader, sizeof(info), nullptr, info);
                Logger::Error(stage_name, " shader compilation failed:\n", info);
                glDeleteShader(shader);
                return 0;
            }
            return shader;
        }
    }

    Shader::~Shader()
    {
        if (program_id)
        {
            glDeleteProgram(program_id);
        }
    }

    void Shader::CreateFromFiles(const std::string& vert_path, const std::string& frag_path)
    {
        // Строки живут до конца функции — c_str() внутри CreateFromSource валиден.
        std::string vertex_source = GetDataFromFile(vert_path);
        std::string fragment_source = GetDataFromFile(frag_path);

        if (vertex_source.empty())
        {
            Logger::Error("Vertex shader file is empty or missing: ", vert_path);
            return;
        }
        if (fragment_source.empty())
        {
            Logger::Error("Fragment shader file is empty or missing: ", frag_path);
            return;
        }

        CreateFromSource(vertex_source, fragment_source);
    }

    void Shader::CreateFromSource(const std::string& vert_source, const std::string& frag_source)
    {
        if (program_id)
        {
            glDeleteProgram(program_id);
            program_id = 0;
        }

        unsigned int vertex_shader = CompileStage(GL_VERTEX_SHADER, vert_source, "Vertex");
        unsigned int fragment_shader = CompileStage(GL_FRAGMENT_SHADER, frag_source, "Fragment");
        if (!vertex_shader || !fragment_shader)
        {
            if (vertex_shader) glDeleteShader(vertex_shader);
            if (fragment_shader) glDeleteShader(fragment_shader);
            return;
        }

        unsigned int program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        int ok = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &ok);
        if (!ok)
        {
            char info[1024];
            glGetProgramInfoLog(program, sizeof(info), nullptr, info);
            Logger::Error("Shader program linking failed:\n", info);
            glDeleteProgram(program);
            return;
        }

        program_id = program;
    }
    
    void Shader::Bind() const
    {
        glUseProgram(program_id);
    }
    void Shader::Unbind() const
    {
        glUseProgram(0);
    }   
    void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
    }
    void Shader::SetUniformVec3(const std::string& name, const glm::vec3& vector) const
    {   
        glUniform3fv(glGetUniformLocation(program_id, name.c_str()), 1, &vector[0]);
    }
    void Shader::SetUniformVec2(const std::string& name, const glm::vec2& vector) const
    {
        glUniform2fv(glGetUniformLocation(program_id, name.c_str()), 1, &vector[0]);
    }
    void Shader::SetUniformFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
    }
    void Shader::SetUniformInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
    }
}
