#include "pch.h"
#include "Quaternion.h"
#include <cmath>
#include "vmath.h"

// copied from https://gist.github.com/shihyu/c5abf3ebff2f5f1cfd32a90968f04a3b, but code is adapted for vmath by @LovelyCatHyt

// http://content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation
// http://www.flipcode.com/documents/matrfaq.html
// http://db-in.com/blog/2011/04/cameras-on-opengl-es-2-x/
// http://wiki.beyondunreal.com/Legacy:Quaternion
// http://clb.demon.fi/MathGeoLib/docs/float3x3.cpp_code.html#612
// http://clb.demon.fi/MathGeoLib/docs/Quat_summary.php
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
// http://www.koders.com/cpp/fid6E231B19C37F95D54405AEADD2C7CE1E84C5CEF1.aspx
// http://forums.create.msdn.com/forums/t/4574.aspx

using Matrix = vmath::mat4;
using Vector = vmath::vec3;

const Quaternion Quaternion::identity(1.0f, 0.0f, 0.0f, 0.0f);

Quaternion::Quaternion() : w(0.0f), x(0.0f), y(0.0f), z(0.0f) { }
Quaternion::Quaternion(float W, float X, float Y, float Z) : w(W), x(X), y(Y), z(Z) { }
Quaternion::~Quaternion() { }

Quaternion::Quaternion(const Quaternion& q) {
    w = q.w;
    x = q.x;
    y = q.y;
    z = q.z;
}

Quaternion& Quaternion::operator=(const Quaternion& q) {
    if (this == &q) return *this;
    w = q.w;
    x = q.x;
    y = q.y;
    z = q.z;
    return *this;
}

Matrix Quaternion::ToMatrix(const Quaternion& q) {
    const float sqw = q.w * q.w;
    const float sqx = q.x * q.x;
    const float sqy = q.y * q.y;
    const float sqz = q.z * q.z;
    // float invs = 1.0f / (sqx + sqy + sqz + sqw);
    const float s = 2.0f / (sqx + sqy + sqz + sqw);

    Matrix matrix = Matrix::identity();

    // use matrix representation from https://zhuanlan.zhihu.com/p/97186723
    matrix[0][0] = 1 - s * (sqy + sqz);
    matrix[1][1] = 1 - s * (sqx + sqz);
    matrix[2][2] = 1 - s * (sqx + sqy);

    float temp1 = s * q.x * q.y;
    float temp2 = s * q.z * q.w;
    matrix[0][1] = temp1 + temp2;
    matrix[1][0] = temp1 - temp2;

    temp1 = s * q.x * q.z;
    temp2 = s * q.w * q.y;
    matrix[0][2] = temp1 - temp2;
    matrix[2][0] = temp1 + temp2;

    temp1 = s * q.y * q.z;
    temp2 = s * q.w * q.x;
    matrix[1][2] = temp1 + temp2;
    matrix[2][1] = temp1 - temp2;

    /*matrix[0][0] = ( sqx - sqy - sqz + sqw) * invs;
    matrix[1][1] = (-sqx + sqy - sqz + sqw) * invs;
    matrix[2][2] = (-sqx - sqy + sqz + sqw) * invs;

    float tmp1 = q.x*q.y;
    float tmp2 = q.z*q.w;
    matrix[1][0] = 2.0f * (tmp1 + tmp2) * invs;
    matrix[0][1] = 2.0f * (tmp1 - tmp2) * invs;

    tmp1 = q.x*q.z;
    tmp2 = q.y*q.w;
    matrix[3][0] = 2.0f * (tmp1 - tmp2) * invs;
    matrix[0][3] = 2.0f * (tmp1 + tmp2) * invs;

    tmp1 = q.y*q.z;
    tmp2 = q.x*q.w;
    matrix[2][1] = 2.0f * (tmp1 + tmp2) * invs;
    matrix[1][2] = 2.0f * (tmp1 - tmp2) * invs;*/ 

    return matrix;
}

bool Quaternion::operator==(Quaternion& rhs) const
{
    return (w == rhs.w && x == rhs.x && y == rhs.y && z == rhs.z);
}

bool Quaternion::operator!=(Quaternion& rhs) const
{
    return !(w == rhs.w && x == rhs.x && y == rhs.y && z == rhs.z);
}

Quaternion& Quaternion::operator*=(Quaternion& rhs) {
    Quaternion q;

    q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    q.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
    q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
    q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;

    *this = q;
    return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& rhs) {
    Quaternion q;

    q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    q.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
    q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
    q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;

    *this = q;
    return *this;
}

Quaternion Quaternion::operator*(Quaternion& rhs) const
{
    Quaternion q;

    q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    q.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
    q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
    q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;

    return q;
}

const Quaternion Quaternion::operator*(const Quaternion& rhs) const
{
    Quaternion q;

    q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    q.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
    q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
    q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;

    return q;
}

Quaternion Quaternion::Normalized() const
{
    const float mag = sqrtf(w * w + x * x + y * y + z * z);
    return Quaternion(w / mag, x / mag, y / mag, z / mag);
}

Quaternion Quaternion::Conjugate() const
{
    return Quaternion(w, -x, -y, -z);
}

void Quaternion::Normalize() {
    const float mag = sqrtf(w * w + x * x + y * y + z * z);

    w /= mag;
    x /= mag;
    y /= mag;
    z /= mag;
}

Vector Quaternion::operator*(const Vector& rhs) const
{
    return vmath::vec3{ ToMatrix(*this) * vmath::vec4{rhs, 0} };
}

Vector Quaternion::operator*(Vector& rhs) const
{
    return vmath::vec3{ ToMatrix(*this) * vmath::vec4{rhs, 0} };
}

Vector operator*(const Vector& v, const Quaternion& m) {
    return vmath::vec3{Quaternion::ToMatrix(m) * vmath::vec4{v, 0} };
}

Vector operator*(Vector& v, Quaternion& m) {
    return vmath::vec3{ Quaternion::ToMatrix(m) * vmath::vec4{v, 0} };
}

Quaternion Quaternion::AngleAxis(float angle, Vector axis) {
    Vector vn = normalize(axis);

    angle *= 0.0174532925f; // To radians!
    angle *= 0.5f;
    const float sinAngle = sin(angle);

    return Quaternion(cos(angle), vn[0] * sinAngle, vn[1] * sinAngle, vn[2] * sinAngle);
}

Quaternion Quaternion::Euler(float X, float Y, float Z) {
    /*X *= 0.0174532925f; // To radians!
    Y *= 0.0174532925f; // To radians!
    Z *= 0.0174532925f; // To radians!

    X *= 0.5f;
    Y *= 0.5f;
    Z *= 0.5f;

    const float sinx = sinf(X);
    const float siny = sinf(Y);
    const float sinz = sinf(Z);
    const float cosx = cosf(X);
    const float cosy = cosf(Y);
    const float cosz = cosf(Z);

    Quaternion q;

    q.w = cosx * cosy * cosz + sinx * siny * sinz;
    q.x = sinx * cosy * cosz + cosx * siny * sinz;
    q.y = cosx * siny * cosz - sinx * cosy * sinz;
    q.z = cosx * cosy * sinz - sinx * siny * cosz;*/
    
    return
        AngleAxis(Z, Vector{0, 0, 1}) *
        AngleAxis(X, Vector{1, 0, 0}) *
        AngleAxis(Y, Vector{0, 1, 0});
}

void Quaternion::SetEuler(float X, float Y, float Z) {
    X *= 0.0174532925f; // To radians!
    Y *= 0.0174532925f; // To radians!
    Z *= 0.0174532925f; // To radians!

    X *= 0.5f;
    Y *= 0.5f;
    Z *= 0.5f;

    const float sinx = sinf(X);
    const float siny = sinf(Y);
    const float sinz = sinf(Z);
    const float cosx = cosf(X);
    const float cosy = cosf(Y);
    const float cosz = cosf(Z);

    w = cosx * cosy * cosz + sinx * siny * sinz;
    x = sinx * cosy * cosz + cosx * siny * sinz;
    y = cosx * siny * cosz - sinx * cosy * sinz;
    z = cosx * cosy * sinz - sinx * siny * cosz;
}

Vector Quaternion::ToAngleAxis(float* angle) const
{
    *angle = acosf(w);
    float sinz = sinf(*angle);
    Vector axis;
    if (fabsf(sinz) > 1e-4f) {
        sinz = 1.0f / sinz;

        axis[0] = x * sinz;
        axis[1] = y * sinz;
        axis[2] = z * sinz;

        *angle *= 2.0f * 57.2957795f;
        if (*angle > 180.0f)
            *angle = 360.0f - *angle;
    }
    else {
        *angle = 0.0f;
        axis[0] = 1.0f;
        axis[1] = 0.0f;
        axis[2] = 0.0f;
    }
    return axis;
}

Quaternion Quaternion::Inverse(Quaternion& rotation) {
    return Quaternion(rotation.w, -1.0f * rotation.x, -1.0f * rotation.y, -1.0f * rotation.z);
}

float Quaternion::Dot(Quaternion& a, Quaternion& b) {
    return (a.w * b.w + a.x * b.x * a.y * b.y + a.z * b.z);
}

float Quaternion::Dot(Quaternion& b) const
{
    return (w * b.w + x * b.x * y * b.y + z * b.z);
}

float Quaternion::Angle(Quaternion& a, Quaternion& b) {
    const float degrees = acosf((b * Quaternion::Inverse(a)).w) * 2.0f * 57.2957795f;
    if (degrees > 180.0f)
        return 360.0f - degrees;
    return degrees;
}

Quaternion operator*(float f, Quaternion& m) {
    return Quaternion(m.w * f, m.x * f, m.y * f, m.z * f);
}

const Quaternion operator*(float f, const Quaternion& m) {
    return Quaternion(m.w * f, m.x * f, m.y * f, m.z * f);
}

Quaternion Quaternion::operator*(float& f) const
{
    return Quaternion(w * f, x * f, y * f, z * f);
}

const Quaternion Quaternion::operator*(const float& f) const
{
    return Quaternion(w * f, x * f, y * f, z * f);
}

Quaternion Quaternion::operator+(Quaternion& rhs) const
{
    return Quaternion(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z);
}

const Quaternion Quaternion::operator+(const Quaternion& rhs) const
{
    return Quaternion(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z);
}

Quaternion Quaternion::Lerp(Quaternion& from, Quaternion& to, float t) {
    const Quaternion src = from * (1.0f - t);
    Quaternion dst = to * t;

    Quaternion q = src + dst;
    return q;
}

Quaternion Quaternion::Slerp(Quaternion& from, Quaternion& to, float t) {
    float cosTheta = Quaternion::Dot(from, to);
    Quaternion temp(to);

    if (cosTheta < 0.0f) {
        cosTheta *= -1.0f;
        temp = temp * -1.0f;
    }

    const float theta = acosf(cosTheta);
    const float sinTheta = 1.0f / sinf(theta);

    return sinTheta * (
        ((Quaternion)(from * sinf(theta * (1.0f - t)))) +
        ((Quaternion)(temp * sinf(t * theta)))
        );
}

//#define m00 right.x
//#define m01 up.x
//#define m02 forward.x
//#define m10 right.y
//#define m11 up.y
//#define m12 forward.y
//#define m20 right.z
//#define m21 up.z
//#define m22 forward.z
//
//Quaternion Quaternion::LookRotation(Vector& lookAt, Vector& upDirection) {
//	Vector forward = lookAt; Vector up = upDirection;
//	Vector::OrthoNormalize(&forward, &up);
//	Vector right = Vector::Cross(up, forward);
//
//	Quaternion ret;
//	ret.w = sqrtf(1.0f + m00 + m11 + m22) * 0.5f;
//	float w4_recip = 1.0f / (4.0f * ret.w);
//	ret.x = (m21 - m12) * w4_recip;
//	ret.y = (m02 - m20) * w4_recip;
//	ret.z = (m10 - m01) * w4_recip;
//
//	return ret;
//}
//
//Quaternion Quaternion::LookRotation(Vector& lookAt) {
//	Vector up = (Vector)Vector::up;
//	Vector forward = lookAt;
//	Vector::OrthoNormalize(&forward, &up);
//	Vector right = Vector::Cross(up, forward);
//
//	Quaternion ret;
//	ret.w = sqrtf(1.0f + m00 + m11 + m22) * 0.5f;
//	float w4_recip = 1.0f / (4.0f * ret.w);
//	ret.x = (m21 - m12) * w4_recip;
//	ret.y = (m02 - m20) * w4_recip;
//	ret.z = (m10 - m01) * w4_recip;
//
//	return ret;
//}
//
//void Quaternion::SetLookRotation(Vector& lookAt) {
//	Vector up = (Vector)Vector::up;
//	Vector forward = lookAt;
//	Vector::OrthoNormalize(&forward, &up);
//	Vector right = Vector::Cross(up, forward);
//
//	w = sqrtf(1.0f + m00 + m11 + m22) * 0.5f;
//	float w4_recip = 1.0f / (4.0f * w);
//	x = (m21 - m12) * w4_recip;
//	y = (m02 - m20) * w4_recip;
//	z = (m10 - m01) * w4_recip;
//}
//
//void Quaternion::SetLookRotation(Vector& lookAt, Vector& upDirection) {
//	Vector forward = lookAt; Vector up = upDirection;
//	Vector::OrthoNormalize(&forward, &up);
//	Vector right = Vector::Cross(up, forward);
//
//	w = sqrtf(1.0f + m00 + m11 + m22) * 0.5f;
//	float w4_recip = 1.0f / (4.0f * w);
//	x = (m21 - m12) * w4_recip;
//	y = (m02 - m20) * w4_recip;
//	z = (m10 - m01) * w4_recip;
//}
//
//#undef m00
//#undef m01
//#undef m02
//#undef m10
//#undef m11
//#undef m12
//#undef m20
//#undef m21
//#undef m22
