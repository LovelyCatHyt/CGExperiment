#pragma once
#include "../GLITY/Glity-All.h"
class SquareDriver
{
private:
	float _timer;
    GLint _sinTimeLoc;
public:
	float loop;
	float maxScale;
	float minScale;
	SquareDriver(float loop, float maxScale, float minScale);
	void Update(GameObject& obj);
    void Awake(GameObject& obj);
};

