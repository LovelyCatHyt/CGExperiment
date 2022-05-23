#include "stdafx.h"
#include "CameraDriver.h"

CameraDriver::CameraDriver(GameObject& obj) : Component(&obj), IUpdate()
{
}

std::string CameraDriver::Name()
{
    return "Camera driver";
}

void CameraDriver::Update(GameObject& obj)
{
    // obj.GetTransform().SetRotation({0, Time::time * 180.0f, 0});
    float dz = 0;
    float dx = 0;
    float speed = .8f;
    if(Input::GetKey('a')) dx -= speed * Time::deltaTime;
    if(Input::GetKey('d')) dx += speed * Time::deltaTime;
    if (Input::GetKey('w')) dz += speed * Time::deltaTime;
    if (Input::GetKey('s')) dz -= speed * Time::deltaTime;
    auto pos = obj.GetTransform().GetPosition();
    pos += vmath::vec3{-dx, 0, dz};
    obj.GetTransform().SetPosition(pos);
}

