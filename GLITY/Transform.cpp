#include "pch.h"
#include "Transform.h"

#include <algorithm>
#include <utility>

// copilot 打这种代码直接起飞
template <typename T>
vmath::mat4 RotateX(T angle)
{
    angle *= 0.01745329251994329547f;
    return vmath::mat4{
        vmath::vec4{1, 0, 0, 0},
        vmath::vec4{0, cos(angle), sin(angle), 0},
        vmath::vec4{0, -sin(angle), cos(angle), 0},
        vmath::vec4{0, 0, 0, 1}
    };
}
template <typename T>
vmath::mat4 RotateY(T angle)
{
    angle *= 0.01745329251994329547f;
    return vmath::mat4{
        vmath::vec4{cos(angle), 0, -sin(angle), 0},
        vmath::vec4{0, 1, 0, 0},
        vmath::vec4{sin(angle), 0, cos(angle), 0},
        vmath::vec4{0, 0, 0, 1}
    };
}
template <typename T>
vmath::mat4 RotateZ(T angle)
{
    angle *= 0.01745329251994329547f;
    return vmath::mat4{
        vmath::vec4{cos(angle), sin(angle), 0, 0},
        vmath::vec4{-sin(angle), cos(angle), 0, 0},
        vmath::vec4{0, 0, 1, 0},
        vmath::vec4{0, 0, 0, 1}
    };
}

vmath::mat4 MatFromEuler(vmath::vec3 euler)
{
    // Rz * Rx * Ry
    return
        RotateZ(euler[2]) *
        RotateX(euler[0]) *
        RotateY(euler[1]);
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

vmath::Tmat4<float> Transform::WorldToLocalMat4X4()
{
    // 和 Construct 反着写就行了
    return vmath::scale(1.0f / _scale[0], 1.0f / _scale[1], 1.0f / _scale[2]) *
           MatFromEuler(-1.0f * _euler) *
           vmath::translate(-_position[0], -_position[1], -_position[2]);
}

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
