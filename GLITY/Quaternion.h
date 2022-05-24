#ifndef _H_QUATERNION_
#define _H_QUATERNION_
#include "vmath.h"

class Quaternion {
public:
  float w, x, y, z;
public:
	Quaternion();
	Quaternion(float W, float X, float Y, float Z);
	Quaternion(const Quaternion& q);
	~Quaternion();
	Quaternion& operator=(const Quaternion&);

	bool operator==(Quaternion& rhs) const;
	bool operator!=(Quaternion& rhs) const;
	
	Quaternion& operator*=(Quaternion& rhs);
	Quaternion& operator*=(const Quaternion& rhs);
	Quaternion operator*(Quaternion& rhs) const;
	const Quaternion operator*(const Quaternion& rhs) const;
	Quaternion operator*(float& rhs) const;
	const Quaternion operator*(const float& rhs) const;
	Quaternion operator+(Quaternion& rhs) const;
	const Quaternion operator+(const Quaternion& rhs) const;
	vmath::vec3 operator*(vmath::vec3& rhs) const;
	vmath::vec3 operator*(const vmath::vec3& rhs) const;

	Quaternion Normalized() const;
	void Normalize();
	Quaternion Conjugate() const; // Same as inverse

	vmath::vec3 ToAngleAxis(float* angle) const;
	void SetEuler(float X, float Y, float Z);
	float Dot(Quaternion& b) const;
	void SetLookRotation(vmath::vec3& lookAt);
	void SetLookRotation(vmath::vec3& lookAt, vmath::vec3& upDirection);

	// static Quaternion LookRotation(vmath::vec3& lookAt);
	// static Quaternion LookRotation(vmath::vec3& lookAt, vmath::vec3& upDirection);
	static Quaternion Slerp(Quaternion& from, Quaternion& to, float t);
	static Quaternion Lerp(Quaternion& from, Quaternion& to, float t);
	static float Angle(Quaternion& a, Quaternion& b);
	static float Dot(Quaternion& a, Quaternion& b);
	static Quaternion AngleAxis(float angle, vmath::vec3 axis);
	static Quaternion Inverse(Quaternion& rotation);
	static Quaternion Euler(float X, float Y, float Z);
	static vmath::mat4 ToMatrix(const Quaternion& q);

	static const Quaternion identity;
};

vmath::vec3 operator*(const vmath::vec3& v, const Quaternion& m);
vmath::vec3 operator*(vmath::vec3& v, Quaternion& m);
Quaternion operator*(float f, Quaternion& m);
const Quaternion operator*(float f, const Quaternion& m);

#endif
