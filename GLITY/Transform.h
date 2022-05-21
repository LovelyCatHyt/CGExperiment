#pragma once
#include "pch.h"
#include "vmath.h"

class Transform
{
private:
	vmath::vec3	_position{ 0,0,0 };
	vmath::vec3 _euler{ 0,0,0 };
	vmath::vec3 _scale{1, 1, 1};
	vmath::mat4 _mat = vmath::mat4::identity();
	
	void ConstructMat();
public:
	Transform(vmath::vec3 pos, vmath::vec3 rot);
	Transform();
	vmath::mat4 LocalToWorldMat4X4() const;
	// vmath::Tmat4<float> WorldToLocalMat4X4();
	vmath::vec3 GetPosition() const;
	void SetPosition(const vmath::vec3& pos);
	vmath::vec3 GetRotation() const;
	void SetRotation(const vmath::vec3& rot);
	vmath::vec3 GetScale() const;
	void SetScale(const vmath::vec3& scl);
};

