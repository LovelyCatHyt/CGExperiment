#include "stdafx.h"
#include "CameraDriver.h"
#include "../GLITY/Quaternion.h"

CameraDriver::CameraDriver(GameObject& obj) : Component(&obj), IUpdate(),
mouseX(0), mouseY(0)
{
}

std::string CameraDriver::Name()
{
    return "Camera driver";
}

void CameraDriver::Update(GameObject& obj)
{
    // 位移
    float dz = 0;
    float dx = 0;
    const float speed = 4.0f;
    if (Input::GetKey('a')) dx -= speed * Time::deltaTime;
    if (Input::GetKey('d')) dx += speed * Time::deltaTime;
    if (Input::GetKey('w')) dz += speed * Time::deltaTime;
    if (Input::GetKey('s')) dz -= speed * Time::deltaTime;
    auto& tran = obj.GetTransform();
    auto pos = tran.GetPosition();
    /*if (dx != 0 || dz != 0)
    {
        auto r = tran.Right();
        auto f = tran.Forward();
        std::cout << "right + (" << toString(r) << "), (" << toString(f) << ")" << std::endl;
    }*/
    pos += dx * tran.Right() + dz * tran.Forward();
    tran.SetPosition(pos);

    // 鼠标旋转
    if (Input::GetMouseButtonDown(0) || Input::GetMouseButtonDown(2))
    {
        mouseX = Input::mousePosition[0];
        mouseY = Input::mousePosition[1];
    }
    else if (Input::GetMouseButton(0) || Input::GetMouseButton(2))
    {
        const auto rotateDelta = 60.0f * Time::deltaTime;

        const auto mouseDx = Input::mousePosition[0] - mouseX;
        const auto mouseDy = Input::mousePosition[1] - mouseY;
        if (mouseDx != 0 || mouseDy != 0)
        {
            // std::cout<<"dx: "<<mouseDx<<", dy: "<<mouseDy<<std::endl;
        }

        auto rot = tran.GetRotation();
        // TODO: fix this WRONG usage
        // euler = Quaternion::Euler(0, 1, 0) * euler;
        rot = Quaternion::Euler(0, mouseDx * rotateDelta, 0) * rot * Quaternion::Euler(mouseDy * rotateDelta, 0, 0);
        tran.SetRotation(rot);

        mouseX += mouseDx;
        mouseY += mouseDy;
    }

    // 切换模式
    if(Input::GetKeyUp('p'))
    {
        (*Camera::main).isOrthoMode = !(*Camera::main).isOrthoMode;
    }

    // 切换背面裁剪
    if(Input::GetKeyDown('b'))
    {
        MeshRenderer::cullFace = !MeshRenderer::cullFace;
        MeshRenderer::depthTest = !MeshRenderer::depthTest;
    }

    // 点光源位置

    MeshRenderer::lightPos = tran.GetPosition();
}

