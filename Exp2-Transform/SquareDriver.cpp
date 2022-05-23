#include "stdafx.h"
#include "SquareDriver.h"
#include "Time.h"

SquareDriver::SquareDriver(float loop, float maxScale, float minScale):
    Component(nullptr), 
	_timer(0), loop(loop), _sinTimeLoc(0),
	maxScale(maxScale),
	minScale(minScale)
{
}

void SquareDriver::Update(GameObject& obj)
{
    // 随便改改缩放
	const auto t_sin = sin(_timer/loop * 6.2831853f)*0.5f + 0.5f;
	const auto t_cos = cos(_timer/loop * 6.2831853f)*0.5f + 0.5f;
	const auto scale = vmath::vec3{minScale*t_sin + maxScale*(1-t_sin), minScale*t_cos + maxScale *(1- t_cos), 1};
	// obj.GetTransform().SetScale(scale);
	_timer += Time::deltaTime;
	_timer = fmod(_timer, loop);
    // 改一下 uniform
    glUniform3f(_sinTimeLoc, sin(Time::time * .1f), sin(Time::time), sin(Time::time * 10.0f));
}

void SquareDriver::Awake(GameObject& obj)
{
    _sinTimeLoc = obj.Renderer().GetUniformLoc("sinTime");
    _gameObject = &obj;
}

std::string SquareDriver::Name()
{
    return "SquareDriver";
}   
