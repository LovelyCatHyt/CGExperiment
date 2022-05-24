#include "stdafx.h"
#include "CubeDriver.h"
#include "Time.h"

CubeDriver::CubeDriver(float loop, float maxScale, float minScale) :
    Component(nullptr), IAwake(), IUpdate(),
    _timer(0), loop(loop), _sinTimeLoc(0),
    maxScale(maxScale),
    minScale(minScale)
{
}

void CubeDriver::Update(GameObject& obj)
{
    auto& r = obj.Renderer();
    if(Input::GetKeyDown('t')) r.enabled = !r.enabled;
    obj.GetTransform().SetRotation({0, -Time::time * 90, 0});
}

void CubeDriver::Awake(GameObject& obj)
{
    _sinTimeLoc = obj.Renderer().GetUniformLoc("sinTime");
    _gameObject = &obj;
}

std::string CubeDriver::Name()
{
    return "SquareDriver";
}
