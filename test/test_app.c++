#include "test_app.h"
#include "test_scene.h"

#include "renderer/object3d.h"

void TestApp::Init()
{
    current_scene = new TestScene();

    camera.transform.position = glm::vec3(0.0f, 0.0f, 5.0f);
    camera.aspect = static_cast<float>(wnd->width) / static_cast<float>(wnd->height);

    DELIB::Object3D* cube = DELIB::CreateObject3D(DELIB::Primitive3D::CreateCube(1.0f));
    cube->name = "cube";
    cube->transform.position = glm::vec3(-1.5f, 0.0f, 0.0f);
    current_scene->AddEntity(cube);

    DELIB::Object3D* sphere = DELIB::CreateObject3D(DELIB::Primitive3D::CreateSphere(0.7f, 24, 16));
    sphere->name = "sphere";
    sphere->transform.position = glm::vec3(1.5f, 0.0f, 0.0f);
    current_scene->AddEntity(sphere);

    DELIB::Object3D* plane = DELIB::CreateObject3D(DELIB::Primitive3D::CreatePlane(6.0f, 6.0f));
    plane->name = "floor";
    plane->transform.position = glm::vec3(0.0f, -1.0f, 0.0f);
    plane->transform.rotation = glm::vec3(-90.0f, 0.0f, 0.0f); // XY -> XZ, нормаль +Y
    current_scene->AddEntity(plane);
}

void TestApp::Update(float dt)
{
    if (current_scene)
    {
        current_scene->Update(dt);
    }

    for (DELIB::Entity* entity : current_scene->entities)
    {
        DELIB::Object3D* object = dynamic_cast<DELIB::Object3D*>(entity);
        if (!object)
        {
            continue;
        }
        if (object->name != "floor")
        {
            object->transform.RotateY(dt * 30.0f); // градусы в секунду
            object->transform.RotateX(dt * 15.0f);
        }
        renderer->RenderObject(*object, camera);
    }

    camera.Update(dt);
    // camera.aspect = wnd->width/wnd->height;
    // camera.transform.RotateY(dt*30.0f);
    // camera.transform.position.z += dt*20.0f; 
}
