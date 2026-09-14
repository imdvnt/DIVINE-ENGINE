#include "triangle3d.h"

#include <glm/gtc/constants.hpp>

namespace DELIB
{
    namespace
    {
        // Треугольник с общей нормалью на все три вершины (плоская грань).
        Triangle3D MakeTriangle(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2,
                                const glm::vec2& uv0, const glm::vec2& uv1, const glm::vec2& uv2,
                                const glm::vec3& normal)
        {
            Triangle3D tri;
            tri.vertices[0] = p0; tri.vertices[1] = p1; tri.vertices[2] = p2;
            tri.normals[0] = normal; tri.normals[1] = normal; tri.normals[2] = normal;
            tri.uvs[0] = uv0; tri.uvs[1] = uv1; tri.uvs[2] = uv2;
            return tri;
        }

        // Плоский квад из двух треугольников. Вершины против часовой стрелки,
        // если смотреть со стороны нормали: p0 - левый нижний, p1 - правый нижний,
        // p2 - правый верхний, p3 - левый верхний.
        void AddQuad(Mesh3D& mesh,
                     const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3,
                     const glm::vec3& normal)
        {
            const glm::vec2 uv0(0.0f, 0.0f), uv1(1.0f, 0.0f), uv2(1.0f, 1.0f), uv3(0.0f, 1.0f);
            mesh.push_back(MakeTriangle(p0, p1, p2, uv0, uv1, uv2, normal));
            mesh.push_back(MakeTriangle(p0, p2, p3, uv0, uv2, uv3, normal));
        }
    }

    Model3D LoadModelFromOBJ(const std::string& filepath)
    {
        // Implement OBJ loading logic here
        // For now, return an empty model
        return Model3D();
    }

    Model3D LoadModelFromMDL(const std::string& filepath)
    {
        // Implement MDL loading logic here
        // For now, return an empty model
        return Model3D();
    }

    // Куб с центром в начале координат, 6 граней по 2 треугольника,
    // нормали наружу, UV (0..1) на каждой грани.
    Model3D Primitive3D::CreateCube(float size)
    {
        const float h = size * 0.5f;
        Mesh3D mesh;
        mesh.reserve(12);

        // +Z (front)
        AddQuad(mesh, {-h, -h,  h}, { h, -h,  h}, { h,  h,  h}, {-h,  h,  h}, { 0,  0,  1});
        // -Z (back)
        AddQuad(mesh, { h, -h, -h}, {-h, -h, -h}, {-h,  h, -h}, { h,  h, -h}, { 0,  0, -1});
        // +X (right)
        AddQuad(mesh, { h, -h,  h}, { h, -h, -h}, { h,  h, -h}, { h,  h,  h}, { 1,  0,  0});
        // -X (left)
        AddQuad(mesh, {-h, -h, -h}, {-h, -h,  h}, {-h,  h,  h}, {-h,  h, -h}, {-1,  0,  0});
        // +Y (top)
        AddQuad(mesh, {-h,  h,  h}, { h,  h,  h}, { h,  h, -h}, {-h,  h, -h}, { 0,  1,  0});
        // -Y (bottom)
        AddQuad(mesh, {-h, -h, -h}, { h, -h, -h}, { h, -h,  h}, {-h, -h,  h}, { 0, -1,  0});

        return Model3D{ mesh };
    }

    // Квад в плоскости XY с центром в начале координат, нормаль +Z
    // (смотрит на камеру по умолчанию). Для пола поверни на -90° по X.
    Model3D Primitive3D::CreatePlane(float width, float height)
    {
        const float hw = width * 0.5f;
        const float hh = height * 0.5f;
        Mesh3D mesh;
        mesh.reserve(2);
        AddQuad(mesh, {-hw, -hh, 0}, {hw, -hh, 0}, {hw, hh, 0}, {-hw, hh, 0}, {0, 0, 1});
        return Model3D{ mesh };
    }

    // UV-сфера: rings - число поясов по широте, segments - по долготе.
    // Нормаль в каждой вершине - нормализованная позиция (гладкое затенение).
    Model3D Primitive3D::CreateSphere(float radius, int segments, int rings)
    {
        if (segments < 3) segments = 3;
        if (rings < 2) rings = 2;

        // Точка на сфере: ring 0 - северный полюс, ring == rings - южный.
        auto point = [&](int ring, int segment) -> glm::vec3
        {
            const float phi = glm::pi<float>() * static_cast<float>(ring) / static_cast<float>(rings);
            const float theta = glm::two_pi<float>() * static_cast<float>(segment) / static_cast<float>(segments);
            return glm::vec3(glm::sin(phi) * glm::cos(theta),
                             glm::cos(phi),
                             glm::sin(phi) * glm::sin(theta));
        };
        auto uv = [&](int ring, int segment) -> glm::vec2
        {
            return glm::vec2(static_cast<float>(segment) / static_cast<float>(segments),
                             1.0f - static_cast<float>(ring) / static_cast<float>(rings));
        };
        auto vertex = [&](Triangle3D& tri, int i, int ring, int segment)
        {
            const glm::vec3 n = point(ring, segment);
            tri.vertices[i] = n * radius;
            tri.normals[i] = n;
            tri.uvs[i] = uv(ring, segment);
        };

        Mesh3D mesh;
        mesh.reserve(static_cast<size_t>(rings) * segments * 2);

        for (int r = 0; r < rings; ++r)
        {
            for (int s = 0; s < segments; ++s)
            {
                // Квад между поясами r и r+1, сегментами s и s+1.
                // Обход подобран так, чтобы грани смотрели наружу.
                if (r != 0)
                {
                    Triangle3D tri;
                    vertex(tri, 0, r,     s);
                    vertex(tri, 1, r,     s + 1);
                    vertex(tri, 2, r + 1, s + 1);
                    mesh.push_back(tri);
                }
                if (r != rings - 1)
                {
                    Triangle3D tri;
                    vertex(tri, 0, r,     s);
                    vertex(tri, 1, r + 1, s + 1);
                    vertex(tri, 2, r + 1, s);
                    mesh.push_back(tri);
                }
            }
        }

        return Model3D{ mesh };
    }
}
