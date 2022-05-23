#pragma once
#include "../GLITY/Glity-All.h"
class SquareDriver: public virtual Component, public virtual IUpdate
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
    std::string Name() override;
};

