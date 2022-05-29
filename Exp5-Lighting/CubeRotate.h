#pragma once
#include "../Glity/Glity-All.h"

class CubeRotate : public virtual Component, public virtual IUpdate
{
    bool doRotate;
public:
    explicit CubeRotate(GameObject& obj);

    std::string Name() override;
    void Update(GameObject& obj) override;
};

