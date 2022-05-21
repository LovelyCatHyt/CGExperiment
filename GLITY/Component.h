#pragma once
#include "pch.h"

class Component
{
protected:
	GameObject* _gameObjectPtr;
public:
	explicit Component(GameObject& obj); // �����ó�ʼ��
	explicit Component(GameObject* objPtr); // ��ָ���ʼ��
	GameObject& GetGameObject() const;
	Transform& GetTransform() const;
	// const Transform& GetTransform() const;
};

