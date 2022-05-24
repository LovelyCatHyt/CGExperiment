#pragma once
#include "../GLITY/Glity-All.h"
class CubeDriver: public virtual Component, public virtual IUpdate, public virtual IAwake
{
private:
	float _timer;
    GLint _sinTimeLoc;
public:
	float loop;
	float maxScale;
	float minScale;
	CubeDriver(float loop, float maxScale, float minScale);
	void Update(GameObject& obj) override;
    void Awake(GameObject& obj) override;
    std::string Name() override;
};

