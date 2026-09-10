#pragma once

#include <glm/glm.hpp>

namespace DELIB
{
    struct Transform
    {
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        Transform() : position(0.0f), rotation(0.0f), scale(1.0f) {}

        void RotateX(float angle);
        void RotateY(float angle);
        void RotateZ(float angle);
        void Translate(const glm::vec3& translation);
        void Scale(const glm::vec3& scaling);
    };
}