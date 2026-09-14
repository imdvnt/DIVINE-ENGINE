#pragma once 

#include "renderer/texture.h"

namespace DELIB
{
    class Material
    {
    public:
        Material();
        ~Material();

        Texture* diffuse_texture = nullptr;
        Texture* specular_texture = nullptr;
    };

    Material* CreateMaterial(Texture* diffuse_texture = nullptr, Texture* specular_texture = nullptr);
}