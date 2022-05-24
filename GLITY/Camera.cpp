#include "pch.h"
#include "Camera.h"
#include "vmath.h"

Camera* Camera::main{ nullptr };

Camera::Camera(GameObject& obj) :
    Component(&obj), ILateUpdate(),
    size(3), fov(60), aspect(1), nearPlane(0.01f), farPlane(1000.0f),
    isOrthoMode(false),
    projectMat(vmath::mat4::identity())
{
    if (main && main != this)
    {
        std::cerr << "Camera duplicated!";
    }
    main = this;
}

std::string Camera::Name()
{
    return "Camera";
}

void Camera::LateUpdate(GameObject& obj)
{
    aspect = static_cast<float>(Screen::screenSize[0]) / static_cast<float>(Screen::screenSize[1]);
    
    if (isOrthoMode)
    {
        float t = size * 0.5f;
        float b = -t;
        float r = t * aspect;
        float l = -r;
        projectMat = vmath::mat4
        {
            vmath::vec4{2 / (r - l),        0,                  0,                                      0},
            vmath::vec4{0,                  2 / (t - b),        0,                                      0},
            vmath::vec4{0,                  0,                  -1 / (farPlane - nearPlane),            0},
            vmath::vec4{-(r + l) / (r - l), -(t + b) / (t - b), -nearPlane / (farPlane - nearPlane),    1}
        };
    }
    else
    {
        // deg2rad = PI / 180.0f = 0.01745329251994329547
        float q = 1.0f / tan(fov * 0.5f * 0.01745329251994329547f);
        projectMat = vmath::mat4
        {
            vmath::vec4{q / aspect, 0, 0, 0},
            vmath::vec4{0, q, 0, 0},
            vmath::vec4{0, 0, (nearPlane + farPlane) / (farPlane - nearPlane), 1},
            vmath::vec4{0, 0, (2 * nearPlane * farPlane) / (nearPlane - farPlane), 0}
        };
    }
    projectMat = projectMat * _gameObject->GetTransform().WorldToLocalMat4X4();
}
