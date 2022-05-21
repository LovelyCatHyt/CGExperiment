#pragma once
#include "../GLITY/Glity-All.h"
class SquareDriver
{
private:
	float _timer;
public:
	float loop;
	float maxScale;
	float minScale;
	SquareDriver(float loop, float maxScale, float minScale);
	void Update(GameObject& obj);
};

