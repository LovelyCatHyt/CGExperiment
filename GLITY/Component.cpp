#include "pch.h"
#include "Component.h"

Component::Component(GameObject& obj) :_gameObjectPtr(&obj)
{
}

Component::Component(GameObject* objPtr) : _gameObjectPtr(objPtr)
{
}

// ReSharper disable once CppMemberFunctionMayBeConst
GameObject& Component::GetGameObject() const
{
	return *_gameObjectPtr;
}

Transform& Component::GetTransform() const
{
	return GetGameObject().GetTransform();
}
