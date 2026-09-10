#pragma once
#include <delib.h>

class TestApp : public DELIB::Application
{
public:
    void Init() override;
    void Update(float dt) override;
};