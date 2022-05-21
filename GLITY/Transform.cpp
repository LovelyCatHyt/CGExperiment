#include "pch.h"
#include "Transform.h"

#include <algorithm>
#include <utility>

template <typename T>
vmath::Tmat4<T> MatFromEuler(vmath::Tvec3<T> euler)
{
	// Rz * Rx * Ry
	return
		vmath::rotate(euler[2], 0.0f, 0.0f, 1.0f) *
		vmath::rotate(euler[0], 1.0f, 0.0f, 0.0f) *
		vmath::rotate(euler[1], 0.0f, 1.0f, 0.0f);
}

Transform::Transform(vmath::vec3 pos, vmath::vec3 rot) :_position(std::move(pos)), _euler(std::move(rot))
{
	ConstructMat();
}

Transform::Transform() : _position(0, 0, 0), _euler(0, 0, 0)
{
	ConstructMat();
}

vmath::mat4 Transform::LocalToWorldMat4X4() const
{
	return _mat;
}

//vmath::Tmat4<float> Transform::WorldToLocalMat4X4()
//{
//	
//}



void Transform::ConstructMat()
{
	_mat = translate(_position) * MatFromEuler(_euler) * vmath::scale(_scale[0], _scale[1], _scale[2]);
}

vmath::vec3 Transform::GetPosition() const
{
	return _position;
}

void Transform::SetPosition(const vmath::vec3& pos)
{
	_position = pos;
	ConstructMat();
}

vmath::vec3 Transform::GetRotation() const
{
	return _euler;
}

void Transform::SetRotation(const vmath::vec3& rot)
{
	_euler = rot;
	ConstructMat();
}

vmath::vec3 Transform::GetScale() const
{
	return _scale;
}

void Transform::SetScale(const vmath::vec3& scl)
{
	_scale = scl;
	ConstructMat();
}
