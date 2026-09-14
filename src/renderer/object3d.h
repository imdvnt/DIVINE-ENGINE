#pragma once 
#include <delib.h>

#include "common/triangle3d/triangle3d.h"
#include "common/transform/transform.h"
#include "renderer/shader.h"
#include "renderer/material.h"

namespace DELIB
{
    class Object3D : public Entity
    {
    public:
        Model3D model;
        Material* material = nullptr;
        Shader* shader = nullptr;
        Transform transform = Transform();

        Object3D() {
            name = "Object3D";
            Init();
        };
        ~Object3D() override {};
        void Init() override {};
        void Update(float dt) override {};
    };

    Object3D* CreateObject3D(const Model3D& model, Material* material = nullptr, Shader* shader = nullptr);
}
