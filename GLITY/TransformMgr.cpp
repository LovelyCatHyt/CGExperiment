#include "pch.h"
#include "TransformMgr.h"

std::vector<Transform> TransformMgr::Transforms;

int TransformMgr::GenerateTransform()
{
	//Transform t{};
	Transforms.emplace_back();
	return Transforms.size() - 1;
}

Transform& TransformMgr::Get(const int& id)
{
	return Transforms[id];
}

void TransformMgr::Remove(Transform& target)
{
	for (int i = 0; i < Transforms.size(); i++)
	{
		if (&Transforms[i] == &target)
		{
			// TODO: remove transform at i
		}
	}
}
