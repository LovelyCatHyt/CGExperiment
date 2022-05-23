#pragma once
#include "pch.h"
#include "Glity-All.h"
#include "GlityEntry.h"
#include <vector>


class IUpdate;
class Component;
class MeshRenderer;

class GameObject
{
private:
	Transform* _transform;
	MeshRenderer* _renderer;
    std::vector<Component*> _components;
    std::vector<IUpdate*> _updatables;
    friend GlityEntry;
    friend Transform::Transform(::GameObject& obj);
    friend Transform::Transform(Transform&& other) noexcept;

    void Awake();
    /// <summary>
    /// 更新 GameObject, 需要每帧调用一次
    /// </summary>
    void Update();

public:
    static std::vector<GameObject> gameObjects;

	GameObject();
	[[nodiscard]] Transform& GetTransform() const;
	void RegisterRenderer(MeshRenderer& renderer);
	[[nodiscard]] MeshRenderer& Renderer() const;
    /// <summary>
    /// 添加用于监听 GameObject 事件的 Component
    /// </summary>
    void AddComponent(Component& component);
    template <class T>
    T& GetComponent();
};

template <class T>
T& GameObject::GetComponent()
{
    for (auto* _com : _components)
    {
        T* temp = dynamic_cast<T*>(_com);
        if(temp) return *temp;
    }
    return *static_cast<T*>(nullptr);
}

template <>
inline MeshRenderer& GameObject::GetComponent<MeshRenderer>()
{
    return Renderer();
}
