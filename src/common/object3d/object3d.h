#pragma once 
#include <delib.h>

#include "common/triangle3d/triangle3d.h"
#include "common/transform/transform.h"

namespace DELIB
{
    class Object3D : public Entity
    {
        Model3D model;
        Shader* shader = nullptr;
        Transform transform = Transform();
    public:
        Object3D();
        void Update (float dt) override;

        void SetModel(const Model3D& model);
        void SetShader(Shader* shader);
        void SetTransform(const Transform& transform);
        const Model3D& GetModel() const;
        Shader* GetShader() const;
        const Transform& GetTransform() const;
    };
}
