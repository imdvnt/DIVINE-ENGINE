#pragma once 

#include <string>

namespace DELIB
{
    class Texture
    {
    public:
        unsigned int id;
        std::string name;
        int width;
        int height;
        int channels;

        Texture() : id(0), name(""), width(0), height(0), channels(0) {}
        Texture(const std::string& path) : id(0), name(""), width(0), height(0), channels(0)
        {
            LoadFromFile(path);
        }

        void LoadFromFile(const std::string& path);
        void Bind(unsigned int slot = 0) const;
        void Unbind() const;
    };
}