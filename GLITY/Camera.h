#pragma once
#include "pch.h"
#include "Glity-All.h"
#include "ILateUpdate.h"

class Camera: public virtual Component, public virtual ILateUpdate
{

public:
    static Camera* main;

    Camera(GameObject& obj);

    float size;
    float fov;
    float aspect;
    float nearPlane;
    float farPlane;
    vmath::mat4 projectMat;
    bool isOrthoMode;

    std::string Name() override;
    void LateUpdate(GameObject& obj) override;
};

