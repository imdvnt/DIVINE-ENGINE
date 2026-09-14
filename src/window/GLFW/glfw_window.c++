#include "glfw_window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <delog.hpp>

namespace DELIB
{
    namespace
    {
        void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
        {
            auto* self = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            if (self)
            {
                self->width = width;
                self->height = height;
            }
            glViewport(0, 0, width, height);
        }
    }

    void GLFWWindow::Init()
    {
        Logger::Info("Initializing GLFW window...");

        if (context)
        {
            Logger::Warn("Init() ignored: GLFW window already initialized.");
            return;
        }

        if (!glfwInit())
        {
            Logger::Error("glfwInit() failed.");
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (!window) {
            fprintf(stderr, "Failed to create GLFW window\n");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        context = window;

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            fprintf(stderr, "Failed to initialize GLAD\n");
            glfwDestroyWindow(window);
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    }

    void GLFWWindow::Destroy()
    {
        if (context)
        {
            glfwDestroyWindow(static_cast<GLFWwindow*>(context));
            context = nullptr;
        }
        Logger::Info("Terminating GLFW...");
        glfwTerminate();
    }

    void GLFWWindow::PollEvents()
    {
        glfwPollEvents();
    }

    bool GLFWWindow::ShouldClose()
    {
        return glfwWindowShouldClose(static_cast<GLFWwindow*>(context));
    }

    void GLFWWindow::SwapBuffers()
    {
        glfwSwapBuffers(static_cast<GLFWwindow*>(context));
    }
}
