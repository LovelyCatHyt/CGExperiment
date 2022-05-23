#include "pch.h"
#include "Glity-All.h"

std::vector<GameObject> GameObject::gameObjects;

GameObject::GameObject()
{
    _transform = &TransformMgr::GenerateTransform(*this);
    _renderer = nullptr;
}

GameObject::GameObject(GameObject&& other) noexcept :
    _transform(other._transform),
    _renderer(other._renderer),
    _components(std::move(other._components)),
    _updateList(std::move(other._updateList)),
    _lateUpdateList(std::move(other._lateUpdateList))

{
    other._transform = nullptr;
    other._renderer = nullptr;
    if (_transform)
    {
        _transform->RefreshGameObjectPtr(this);
    }
    if (_renderer)
    {
        _renderer->RefreshGameObjectPtr(this);
    }
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
        auto* updatePtr = dynamic_cast<IUpdate*>(component);
        if (updatePtr
            )
        {
            _updateList.emplace_back(updatePtr
            );
        }

        auto* lateUpdatePtr = dynamic_cast<ILateUpdate*>(component);
        if (lateUpdatePtr)
        {
            _lateUpdateList.emplace_back(lateUpdatePtr);
        }

        auto* awakePtr = dynamic_cast<IAwake*>(component);
        if (awakePtr)
        {
            // 默认无论如何都要 Awake, 其它细节先不管
            awakePtr->Awake(*this);
        }
    }
}

void GameObject::Update()
{
    for (auto* updatable : _updateList)
    {
        if (updatable->enabled)
            updatable->Update(*this);
    }
}

void GameObject::LateUpdate()
{
    for (auto* updatable : _lateUpdateList)
    {
        if (updatable->enabled)
            updatable->LateUpdate(*this);
    }
}

Component& GameObject::AddComponent(Component& component)
{
    return *_components.emplace_back(&component);
}
