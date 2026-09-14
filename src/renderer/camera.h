#pragma once
#include <delib.h>
#include <glm/glm.hpp>

#include "common/transform/transform.h"

namespace DELIB
{
    enum class ProjectionType { Perspective, Orthographic };
    
    class Camera : public Entity
    {
    public:
        Transform transform;
        ProjectionType projection_type = ProjectionType::Perspective;
        float fov = 45.0f;
        float near_plane = 0.1f;
        float far_plane = 100.0f;
        float aspect = 800.0f / 600.0f;
        glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        Camera() {Init();}
        void Init() override;
        void Update(float dt) override;
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;
    };
}