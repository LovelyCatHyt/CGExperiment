#pragma once
#include <vector>
#include "Transform.h"
class TransformMgr
{
private:
	static std::vector<Transform> Transforms;
public:
	static Transform& GenerateTransform(GameObject& obj);
	static Transform& Get(const int& id);
	static void Remove(Transform&);
};

