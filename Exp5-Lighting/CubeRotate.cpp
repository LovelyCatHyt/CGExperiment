#include "stdafx.h"
#include "CubeRotate.h"

CubeRotate::CubeRotate(GameObject& obj) : Component(&obj), IUpdate()
{
}

std::string CubeRotate::Name()
{
    return "TextureParaSetter";
}

void CubeRotate::Update(GameObject& obj)
{
    if(Input::GetKeyDown('r'))
    {
        doRotate = !doRotate;
    }
    if(doRotate)
    {
        auto& tran = obj.GetTransform();
        auto oldRot = tran.GetRotation();
        tran.SetRotation(Quaternion::Euler(0, Time::deltaTime * 60, 0) * oldRot);
    }
}
