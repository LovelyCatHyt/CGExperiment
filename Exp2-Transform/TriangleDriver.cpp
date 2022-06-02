#include "stdafx.h"
#include "TriangleDriver.h"

TriangleDriver::TriangleDriver() : Component(nullptr), IUpdate(), IAwake(),
    _angleLoc(-1), _centerLoc(-1), _sinTimeLoc(-1), _angle(0)
{

}

std::string TriangleDriver::Name()
{
    return "TriangleDriver";
}

void TriangleDriver::Awake(GameObject& obj)
{
    _angleLoc = obj.Renderer().GetUniformLoc("angle");
    _centerLoc = obj.Renderer().GetUniformLoc("center");
    _sinTimeLoc = obj.Renderer().GetUniformLoc("sinTime");
}

void TriangleDriver::Update(GameObject& obj)
{
    glUseProgram(obj.Renderer().shaderProgram);

    const vmath::vec2 center = Screen::ScreenToNdc(Input::mousePosition[0], Input::mousePosition[1]);
    glUniform2f(_centerLoc, center[0], center[1]);
    glUniform3f(_sinTimeLoc, sin(Time::time * 0.1f), sin(Time::time), sin(Time::time * 10.0f));
    const auto left = Input::GetKey('z');
    const auto right = Input::GetKey('x');
    if (left || right)
    {
        const float speed = 3.1415926535f * 2;
        const float deltaAngle = Time::deltaTime * speed;
        _angle = _angle + (left ? 1.0f : -1.0f) * deltaAngle;
        glUniform1f(_angleLoc, _angle);
    }
}
