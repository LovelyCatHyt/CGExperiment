#pragma once
#include "pch.h"
#include "Glity-All.h"
#include "GlityEntry.h"
#include <vector>


class IUpdate;
class ILateUpdate;
class Component;
class MeshRenderer;

class GameObject
{
private:
	Transform* _transform;
	MeshRenderer* _renderer;
    std::vector<Component*> _components;
    std::vector<IUpdate*> _updateList;
    std::vector<ILateUpdate*> _lateUpdateList;
    friend GlityEntry;
    friend Transform::Transform(::GameObject& obj);
    friend Transform::Transform(Transform&& other) noexcept;

    void Awake();
    /// <summary>
    /// 更新 GameObject, 需要每帧调用一次
    /// </summary>
    void Update();
    /// <summary>
    /// 在所有 Update 之后, 渲染之前执行的更新
    /// </summary>
    void LateUpdate();

public:
    static std::vector<GameObject> gameObjects;

	GameObject();
    GameObject(GameObject&& other) noexcept;
	[[nodiscard]] Transform& GetTransform() const;
	void RegisterRenderer(MeshRenderer& renderer);
	[[nodiscard]] MeshRenderer& Renderer() const;
    /// <summary>
    /// 添加用于监听 GameObject 事件的 Component
    /// </summary>
    Component& AddComponent(Component& component);
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
