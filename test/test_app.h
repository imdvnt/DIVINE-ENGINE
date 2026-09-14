#pragma once
#include <delib.h>
#include "renderer/camera.h"
#include "utility/delog.hpp"

class TestApp : public DELIB::Application
{
    DELIB::Camera camera;
public:
    void Init() override;
    void Update(float dt) override;
};
