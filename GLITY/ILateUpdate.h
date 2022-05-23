#pragma once
#include "pch.h"
#include "Glity-All.h"

class ILateUpdate : public virtual Component
{
public:
    virtual void LateUpdate(GameObject& obj) = 0;
};

