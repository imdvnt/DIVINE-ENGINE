#pragma once 
#include <glm/glm.hpp>

#include <vector>
#include <string>

namespace DELIB
{
    struct Triangle3D
    {
        glm::vec3 vertices[3] {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        };
        glm::vec3 normals[3] {
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
        };
        glm::vec2 uvs[3] {
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(0.0f, 1.0f)
        };
    };

    using Mesh3D = std::vector<Triangle3D>;
    using Model3D = std::vector<Mesh3D>;

    class Primitive3D
    {
    public:
        static Model3D CreateCube(float size = 1.0f);
        static Model3D CreatePlane(float width = 1.0f, float height = 1.0f);
        static Model3D CreateSphere(float radius = 1.0f, int segments = 16, int rings = 16);
    };

    Model3D LoadModelFromOBJ(const std::string& filepath);
    Model3D LoadModelFromMDL(const std::string& filepath);
}