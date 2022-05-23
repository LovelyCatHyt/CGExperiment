#pragma once
#include "pch.h"
#include "vmath.h"
#include "Component.h"
#include "Glity-All.h"

class Transform : public virtual Component
{
private:
	vmath::vec3	_position{ 0,0,0 };
	vmath::vec3 _euler{ 0,0,0 };
	vmath::vec3 _scale{1, 1, 1};
	vmath::mat4 _mat = vmath::mat4::identity();

	void ConstructMat();
public:
	Transform();
	Transform(vmath::vec3 pos, vmath::vec3 rot, vmath::vec3 scale);
    // 用 GameObject 引用进行构造
    explicit Transform(GameObject& obj);
	// 移动构造函数
	Transform(Transform&& other) noexcept;
    ~Transform() override;

    [[nodiscard]] GameObject& GameObject() const;

    [[nodiscard]] vmath::mat4 LocalToWorldMat4X4() const;
	[[nodiscard]] vmath::Tmat4<float> WorldToLocalMat4X4();
    [[nodiscard]] vmath::vec3 GetPosition() const;
	void SetPosition(const vmath::vec3& pos);
    [[nodiscard]] vmath::vec3 GetRotation() const;
	void SetRotation(const vmath::vec3& rot);
    [[nodiscard]] vmath::vec3 GetScale() const;
	void SetScale(const vmath::vec3& scl);
    std::string Name() override;
};

