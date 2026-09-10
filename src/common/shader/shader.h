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
        
        void Create(std::string vert, std::string frag);
        void Bind() const;
        void Unbind() const;
        void Compile() const;
        void SetUniformMat4(const std::string& name, const glm::mat4& matrix) const;
        void SetUniformVec3(const std::string& name, const glm::vec3& vector) const;
        void SetUniformVec2(const std::string& name, const glm::vec2& vector) const;
        void SetUniformFloat(const std::string& name, float value) const;
        void SetUniformInt(const std::string& name, int value) const;
    };
}