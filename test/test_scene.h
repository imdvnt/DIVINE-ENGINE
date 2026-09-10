#pragma once
#include <delib.h>

class TestScene : public DELIB::Scene
{
public:
    void Init() override;
    void Update(float deltaTime) override;
    void Shutdown() override;
};