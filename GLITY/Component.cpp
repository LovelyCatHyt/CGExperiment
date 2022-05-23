#include "pch.h"
#include "Component.h"

Component::Component(GameObject& obj) :_gameObject(&obj)
{
}

Component::Component(GameObject* objPtr) : _gameObject(objPtr)
{
}

void Component::RefreshGameObjectPtr(GameObject* obj)
{
    _gameObject = obj;
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

Component& Component::AddComponent(Component& component) const
{
    return _gameObject->AddComponent(component);
}
