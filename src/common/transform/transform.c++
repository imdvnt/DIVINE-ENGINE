#include "transform.h"

namespace DELIB
{
    void Transform::RotateX(float angle)
    {
        rotation.x += angle;
    }

    void Transform::RotateY(float angle)
    {
        rotation.y += angle;
    }

    void Transform::RotateZ(float angle)
    {
        rotation.z += angle;
    }

    void Transform::Translate(const glm::vec3& translation)
    {
        position += translation;
    }

    void Transform::Scale(const glm::vec3& scaling)
    {
        scale *= scaling;
    }
}