#pragma once

#include <cstdio>
#include <vector>
#include <string>

#include <delog.hpp>
#include "window/window.h"
#include "renderer/renderer.h"

namespace DELIB
{
    class Entity
    {
    public:
        int32_t id;
        std::string name;
        
        virtual ~Entity() {};
        void virtual Init() = 0;
        void virtual Update(float dt) = 0;
    };

    class Scene
    {
    public:
        int32_t id;
        std::string name;
        std::vector<Entity*> entities;

        virtual ~Scene() {};
        void virtual Init() = 0;
        void virtual Update(float dt);
        void virtual Shutdown() = 0;

        void AddEntity(Entity* entity);
        void RemoveEntity(Entity* entity);
    };

    class Application
    {
    public:
        //подключаемые модули приложения
        Window* wnd = nullptr;
        Renderer* renderer = nullptr;

        std::vector<Scene*> scenes;
        Scene* current_scene = nullptr;
    
        ~Application() {
            for (Scene* scene : scenes)
                delete scene;
            current_scene = nullptr;
        };

        // Init виртуальный для загрузки ресурсов и инициализации сцены, мб еще для чего-то
        void virtual Init() = 0;
        void virtual Update(float dt);
    };

    void Run(Application& app);
}