#pragma once
#include "Glity-All.h"

class IAwake : public virtual Component
{
public:
    virtual void Awake(GameObject& obj) = 0;
};

