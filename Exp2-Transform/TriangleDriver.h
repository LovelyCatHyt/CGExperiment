#pragma once
#include "../GLITY/Glity-All.h"

class TriangleDriver : public virtual Component, public virtual IUpdate, public virtual IAwake
{
    GLint _angleLoc;
    GLint _centerLoc;
    GLint _sinTimeLoc;
    float _angle;
public:
    TriangleDriver();
    std::string Name() override;
    void Awake(GameObject& obj) override;
    void Update(GameObject& obj) override;
};

