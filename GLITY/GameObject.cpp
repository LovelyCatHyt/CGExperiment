#include "pch.h"
#include "Glity-All.h"

std::vector<GameObject> GameObject::gameObjects;

GameObject::GameObject()
{
	_transform = &TransformMgr::GenerateTransform(*this);
	_renderer = nullptr;
}

Transform& GameObject::GetTransform() const
{
	return *_transform;
}

void GameObject::RegisterRenderer(MeshRenderer& renderer)
{
	_renderer = &renderer;
}

MeshRenderer& GameObject::Renderer() const
{
	return *_renderer;
}

void GameObject::Update()
{
    for(auto* updatable: _updatables)
    {
        updatable->Update(*this);
    }
}

void GameObject::AddComponent(Component& component)
{
    auto* updatablePtr = dynamic_cast<IUpdate*>(&component);
    if(updatablePtr)
    {
        _updatables.emplace_back(updatablePtr);
    }
    _components.emplace_back(&component);
}
