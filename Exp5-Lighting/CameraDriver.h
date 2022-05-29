#pragma once
#include "../GLITY/Glity-All.h"

class CameraDriver : public virtual Component, public virtual IUpdate
{
public:
    int mouseX;
    int mouseY;

    explicit CameraDriver(GameObject& obj);
    std::string Name() override;
    void Update(GameObject& obj) override;
};

