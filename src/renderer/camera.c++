#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace DELIB
{
    void Camera::Init()
    {
        // Initialize camera properties if needed
    }

    // Пересчитывает forward/up из transform.rotation (градусы):
    //   x - pitch (вверх/вниз), y - yaw (влево/вправо), z - roll.
    // При нулевых углах камера смотрит в -Z, как и раньше.
    void Camera::Update(float dt)
    {
        (void)dt;

        constexpr float max_pitch = 89.0f;
        transform.rotation.x = glm::clamp(transform.rotation.x, -max_pitch, max_pitch);

        glm::mat4 orientation = glm::mat4(1.0f);
        orientation = glm::rotate(orientation, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        orientation = glm::rotate(orientation, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        orientation = glm::rotate(orientation, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        forward = glm::normalize(glm::vec3(orientation * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
        up      = glm::normalize(glm::vec3(orientation * glm::vec4(0.0f, 1.0f,  0.0f, 0.0f)));
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
                return glm::perspective(glm::radians(fov), aspect, near_plane, far_plane);
            case ProjectionType::Orthographic:
                return glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, near_plane, far_plane);
            default:
                return glm::mat4(1.0f);
        }
    }
}