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

void GameObject::Awake()
{
    // 绑定所有监听项目
    for (Component* component : _components)
    {
        auto* updatablePtr = dynamic_cast<IUpdate*>(component);
        if (updatablePtr)
        {
            _updatables.emplace_back(updatablePtr);
        }
        auto* awakablePtr = dynamic_cast<IAwake*>(component);
        if (awakablePtr)
        {
            // 默认无论如何都要 Awake, 其它细节先不管
            awakablePtr->Awake(*this);
        }
    }
}

void GameObject::Update()
{
    for(auto* updatable: _updatables)
    {
        if(updatable->enabled)
            updatable->Update(*this);
    }
}

void GameObject::AddComponent(Component& component)
{
    _components.emplace_back(&component);
}
