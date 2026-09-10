#include "delib.h"
#include "window/window.h"
#include "window/SDL/sdl_window.h"
#include "window/GLFW/glfw_window.h"
#include "renderer/renderer.h"
#include "renderer/software/software_renderer.h"
#include "renderer/opengl/opengl_renderer.h"

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
        Logger::Info("Initializing DELIB framework...");

        app.wnd = new GLFWWindow();
        if (!app.wnd->context)
        {
            Logger::Error("Window initialization failed; aborting startup.");
            return false;
        }
        Logger::Info("Window created: ", app.wnd->width, "x", app.wnd->height);

        app.renderer = new OpenGLRenderer(app.wnd);
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
            Logger::Info("Updating time...");
            Time::Update(0.1f);
            app.renderer->ClearScreen(sin(Time::SinceStart()), 0.0f, 0.0f, 1.0f);
            Logger::Info("Delta time: ", Time::Delta(), " seconds");
            Logger::Info("Polling events and updating application...");
            app.wnd->PollEvents();
            app.Update(Time::Delta());
            Logger::Info("Updating current scene...");
            app.current_scene->Update(Time::Delta());
            // app.current_scene->Draw(app.renderer);

            Logger::Info("Swapping buffers...");
            app.wnd->SwapBuffers();
        }
        Shutdown(app);
    }
}