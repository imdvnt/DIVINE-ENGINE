#include "delib.h"
#include "window/window.h"
#include "window/SDL/sdl_window.h"
#include "window/GLFW/glfw_window.h"
#include "renderer/renderer.h"
#include "renderer/software/software_renderer.h"
#include "renderer/opengl/gl_renderer.h"

#include <delog.hpp>
#include <detime.hpp>

#include <algorithm>
#include <cmath>

namespace DELIB
{
    void Scene::AddEntity(Entity* entity)
    {   
        entities.push_back(entity);
    }

    void Scene::RemoveEntity(Entity* entity)
    {
        entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
    }

    void Scene::Update(float dt)
    {
        for (Entity* entity : entities)
        {
            entity->Update(dt);
        }
    }

    void Application::Update(float dt)
    {
        current_scene->Update(dt);
    }

    bool Init(Application& app)
    {
        app.wnd = new GLFWWindow();
        if (!app.wnd->context)
        {
            Logger::Error("Window initialization failed; aborting startup.");
            return false;
        }
        Logger::Info("Window created: ", app.wnd->width, "x", app.wnd->height);

        app.renderer = new GL_Renderer(app.wnd);
        if (!app.renderer)
        {
            Logger::Error("Renderer initialization failed; aborting startup.");
            return false;
        }

        Logger::Info("application initialization...");
        app.Init();
        Logger::Info("application initialization complete.");
        return true;
    }

    void Shutdown(Application& app)
    {
        Logger::Info("Shutting down DELIB framework...");

        if (app.renderer)
        {
            app.renderer->Destroy();
            delete app.renderer;
            app.renderer = nullptr;
        }

        if (app.wnd)
        {
            app.wnd->Destroy();
            delete app.wnd;
            app.wnd = nullptr;
        }
    }

    void Run(Application& app)
    {
        if (!Init(app))
        {
            Shutdown(app);
            return;
        }

        Time::Reset();
        Logger::Info("Entering main loop...");
        while (!app.wnd->ShouldClose())
        {
            Time::Update(0.1f);

            app.wnd->PollEvents();

            app.renderer->ClearScreen(0.851f, 0.824f, 0.753f, 1.0f);
            app.Update(Time::Delta());
            // Logger::Info("Swapping buffers...");
            app.wnd->SwapBuffers();
        }
        Shutdown(app);
    }
}