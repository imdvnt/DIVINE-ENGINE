#pragma once 
#include <glm/glm.hpp>

#include <vector>

#define Mesh3D std::vector<Triangle3D>
#define Model3D std::vector<Mesh3D>

namespace DELIB
{
    struct Triangle3D
    {
        glm::vec3 vertices[3];
        glm::vec3 normals[3];
        glm::vec2 uvs[3];
    };
}