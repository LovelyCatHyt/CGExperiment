#include "pch.h"
#include "TransformMgr.h"

GameObject::GameObject()
{
	_transformId = TransformMgr::GenerateTransform();
	_renderer = nullptr;
}

Transform& GameObject::GetTransform() const
{
	return TransformMgr::Get(_transformId);
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
	for (const auto& updateCallBack : _updateCallBacks)
	{
		if(updateCallBack) updateCallBack(*this);
	}
}

void GameObject::AddUpdateListener(const std::function<void(GameObject&)>& callback)
{
	_updateCallBacks.emplace_back(callback);
}