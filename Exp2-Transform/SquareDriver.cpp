#include "stdafx.h"
#include "SquareDriver.h"
#include "Time.h"

SquareDriver::SquareDriver(float loop, float maxScale, float minScale):
	_timer(0), loop(loop),
	maxScale(maxScale),
	minScale(minScale)
{
}

void SquareDriver::Update(GameObject& obj)
{
	const auto t_sin = sin(_timer/loop * 6.2831853f)*0.5f + 0.5f;
	const auto t_cos = cos(_timer/loop * 6.2831853f)*0.5f + 0.5f;
	const auto scale = vmath::vec3{minScale*t_sin + maxScale*(1-t_sin), minScale*t_cos + maxScale *(1- t_cos), 1};
	obj.GetTransform().SetScale(scale);
	_timer += Time::deltaTime;
	_timer = fmod(_timer, loop);
}
