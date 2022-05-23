#pragma once
#include "pch.h"
#include <vector>
#include <functional>

class MeshRenderer;

class GameObject
{
private:
	int _transformId;
	MeshRenderer* _renderer;
	std::vector<std::function<void(GameObject&)>> _updateCallBacks;
public:
    static std::vector<GameObject> gameObjects;

	GameObject();
	[[nodiscard]] Transform& GetTransform() const;
	void RegisterRenderer(MeshRenderer& renderer);
	[[nodiscard]] MeshRenderer& Renderer() const;
	/// <summary>
	/// 更新 GameObject, 需要每帧调用一次
	/// </summary>
	void Update();
	void AddUpdateListener(const std::function<void(GameObject&)>& callback);
};
