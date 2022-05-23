#pragma once
#include "pch.h"
#include "Glity-All.h"

class Transform;
class GameObject;

class Component
{
protected:
	GameObject* _gameObject;
	
public:
    bool enabled = true;
    virtual ~Component() = default;
    explicit Component(GameObject& obj); // 以引用初始化
	explicit Component(GameObject* objPtr); // 以指针初始化
    void RefreshGameObjectPtr(GameObject* obj);
	GameObject& GetGameObject() const;
	Transform& GetTransform() const;
    Component& AddComponent(Component& component) const;
    virtual std::string Name() = 0;
	// const Transform& GetTransform() const;
};

