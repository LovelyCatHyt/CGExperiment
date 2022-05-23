#include "pch.h"
#include "Component.h"

Component::Component(GameObject& obj) :_gameObject(&obj)
{
}

Component::Component(GameObject* objPtr) : _gameObject(objPtr)
{
}

// ReSharper disable once CppMemberFunctionMayBeConst
GameObject& Component::GetGameObject() const
{
	return *_gameObject;
}

Transform& Component::GetTransform() const
{
	return GetGameObject().GetTransform();
}
