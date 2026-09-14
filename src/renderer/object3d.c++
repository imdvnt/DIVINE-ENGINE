#include "object3d.h"

namespace DELIB
{
    Object3D* CreateObject3D(const Model3D& model, Material* material, Shader* shader)
    {
        Object3D* object = new Object3D();
        object->model = model;
        object->material = material;
        object->shader = shader;
        return object;
    }
}
