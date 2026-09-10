#include "test_app.h"
#include "test_scene.h"

void TestApp::Init()
{
    current_scene = new TestScene();
}

void TestApp::Update(float dt)
{
    if (current_scene)
    {
        current_scene->Update(dt);
    }

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    float colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
    };
    
    // renderer->DrawTriangle(vertices, colors);

}
