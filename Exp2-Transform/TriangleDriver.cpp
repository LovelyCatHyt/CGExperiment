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
    const float speed = 3.1415926535f * 2;
    glUseProgram(obj.Renderer().shaderProgram);
    const vmath::vec2 center = Screen::ScreenToNdc(Input::mousePosition[0], Input::mousePosition[1]);
    glUniform1f(_timeLoc, Time::time);
    glUniform2f(_centerLoc, center[0], center[1]);
    glUniform3f(_sinTimeLoc, sin(Time::time * 0.1f), sin(Time::time), sin(Time::time * 10.0f));
    const auto left = Input::GetMouseButton(GLUT_LEFT_BUTTON);
    const auto right = Input::GetMouseButton(GLUT_RIGHT_BUTTON);
    if (left || right)
    {
        glUniform1f(_speedLoc, speed * (left? 1.0f : -1.0f));
    }
    else
    {
        glUniform1f(_speedLoc, 0);
    }
}
