#include "stdafx.h"
#include "TriangleDriver.h"

TriangleDriver::TriangleDriver() : Component(nullptr), IUpdate(), IAwake(), _timeLoc(-1), _speedLoc(-1), _centerLoc(-1), _sinTimeLoc(-1)
{

}

std::string TriangleDriver::Name()
{
    return "TriangleDriver";
}

void TriangleDriver::Awake(GameObject& obj)
{
    _timeLoc = obj.Renderer().GetUniformLoc("time");
    _speedLoc = obj.Renderer().GetUniformLoc("speed");
    _centerLoc = obj.Renderer().GetUniformLoc("center");
    _sinTimeLoc = obj.Renderer().GetUniformLoc("sinTime");
}

void TriangleDriver::Update(GameObject& obj)
{
    glCullFace(GL_BACK);
    const float speed = 120;
    obj.GetTransform().SetRotation({0, Time::time * speed, 0});
}
