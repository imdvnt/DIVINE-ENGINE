#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace DELIB
{
    void Camera::Update(float dt)
    {
        
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return glm::lookAt(transform.position, transform.position + forward, up);
    }

    glm::mat4 Camera::GetProjectionMatrix() const
    {
        switch (projection_type)
        {
            case ProjectionType::Perspective:
                return glm::perspective(glm::radians(fov), 800.0f / 600.0f, near_plane, far_plane);
            case ProjectionType::Orthographic:
                return glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, near_plane, far_plane);
            default:
                return glm::mat4(1.0f);
        }
    }
}