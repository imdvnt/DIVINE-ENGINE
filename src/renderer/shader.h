#pragma once 

#include <string>
#include <glm/glm.hpp>

namespace DELIB
{
    struct Shader
    {
        unsigned int id;
        std::string name;
        unsigned int program_id;
        Shader() : id(0), name(""), program_id(0) {}
        Shader(const std::string& vert, const std::string& frag) : id(0), name(""), program_id(0)
        {
            CreateFromFiles(vert, frag);
        }
        ~Shader();

        // Объекты держат Shader*, копия привела бы к двойному glDeleteProgram.
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        bool IsValid() const { return program_id != 0; }

        void CreateFromFiles(const std::string& vert_path, const std::string& frag_path);
        void CreateFromSource(const std::string& vert_source, const std::string& frag_source);
        void Bind() const;
        void Unbind() const;
        void SetUniformMat4(const std::string& name, const glm::mat4& matrix) const;
        void SetUniformVec3(const std::string& name, const glm::vec3& vector) const;
        void SetUniformVec2(const std::string& name, const glm::vec2& vector) const;
        void SetUniformFloat(const std::string& name, float value) const;
        void SetUniformInt(const std::string& name, int value) const;
    };
}
