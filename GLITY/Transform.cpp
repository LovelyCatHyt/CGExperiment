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

Transform::Transform(vmath::vec3 pos, vmath::vec3 rot, vmath::vec3 scale) :
    Component(nullptr),
    _position(std::move(pos)),
    _euler(std::move(rot)),
    _scale(std::move(scale))

{
    ConstructMat();
}

Transform::Transform(::GameObject& obj) : Component(&obj)
{
    obj._transform = this;
}

Transform::Transform() :
    Component(nullptr),
    _position(0, 0, 0),
    _euler(0, 0, 0),
    _scale(1, 1, 1)
{
    ConstructMat();
}

Transform::Transform(Transform&& other) noexcept :
    Component(other._gameObject),
    _position(std::move(other._position)),
    _euler(std::move(other._euler)),
    _scale(std::move(other._scale)),
    _mat(other._mat)
{
    if (_gameObject)
    {
        _gameObject->_transform = this;
    }
}

Transform::~Transform()
= default;

GameObject& Transform::GameObject() const
{
    return *_gameObject;
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

void Transform::SetPosition(const vmath::vec3 & pos)
{
    _position = pos;
    ConstructMat();
}

vmath::vec3 Transform::GetRotation() const
{
    return _euler;
}

void Transform::SetRotation(const vmath::vec3 & rot)
{
    _euler = rot;
    ConstructMat();
}

vmath::vec3 Transform::GetScale() const
{
    return _scale;
}

void Transform::SetScale(const vmath::vec3 & scl)
{
    _scale = scl;
    ConstructMat();
}

std::string Transform::Name()
{
    return "Transform";
}
