#include "stdafx.h"
#include "CubeRotate.h"
#include "../GLITY/ShaderUtil.h"

CubeRotate::CubeRotate(GameObject& obj) : Component(&obj), IUpdate()
{
    _phongShader = ShaderUtil::LoadShaderByName("../Resources/Shaders/Standard.vert", "Shaders/Phong_NoNormal.frag");
    _gouraudShader = ShaderUtil::LoadShaderByName("Shaders/Gouraud");
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
    if(Input::GetKeyDown('1'))
    {
        obj.Renderer().shaderProgram = _gouraudShader;
    }
    if(Input::GetKeyDown('2'))
    {
        obj.Renderer().shaderProgram = _phongShader;
    }
}
