#pragma once
#include "pch.h"
#include "vmath.h"
#include "Quaternion.h"
#include "Component.h"
#include "Glity-All.h"

class Transform : public virtual Component
{
private:
	vmath::vec3	_position{ 0,0,0 };
	Quaternion _rotation{1, 0, 0, 0};
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
    /// <summary>
    /// 返回 Transform 内, 向量(1, 0, 0)在世界空间下的表示
    /// </summary>
    /// <returns></returns>
    vmath::vec3 Right() const;
    /// <summary>
    /// 返回 Transform 内, 向量(0, 0, 1)在世界空间下的表示
    /// </summary>
    /// <returns></returns>
    vmath::vec3 Forward() const;
    /// <summary>
    /// 返回 Transform 内, 向量(0, 1, 0)在世界空间下的表示
    /// </summary>
    /// <returns></returns>
    vmath::vec3 Up() const;
    [[nodiscard]] vmath::vec3 GetPosition() const;
	void SetPosition(const vmath::vec3& pos);
    [[nodiscard]] Quaternion GetRotation() const;
    // [[nodiscard]] vmath::vec3 GetEulerRotation() const;
	void SetRotation(const vmath::vec3& rot);
    void SetRotation(const Quaternion& rotation);
    [[nodiscard]] vmath::vec3 GetScale() const;
	void SetScale(const vmath::vec3& scl);
    std::string Name() override;
};

