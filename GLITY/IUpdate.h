#pragma once
#include "pch.h"
#include "Glity-All.h"
class IUpdate: public virtual Component
{
public:
    virtual ~IUpdate() = default;
    virtual void Update(GameObject& obj) = 0;
};

