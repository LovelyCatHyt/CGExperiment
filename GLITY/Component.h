#pragma once
#include "pch.h"

class Component
{
protected:
	GameObject* _gameObjectPtr;
public:
	explicit Component(GameObject& obj); // 以引用初始化
	explicit Component(GameObject* objPtr); // 以指针初始化
	GameObject& GetGameObject() const;
	Transform& GetTransform() const;
	// const Transform& GetTransform() const;
};

