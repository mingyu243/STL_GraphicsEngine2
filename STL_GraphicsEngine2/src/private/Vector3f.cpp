#include "Vector3f.h"
#include <math.h>

const Vector3f Vector3f::Right = Vector3f(1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::Forward = Vector3f(0.0f, 0.0f, 1.0f);
const Vector3f Vector3f::Up = Vector3f(0.0f, 1.0f, 0.0f);
const Vector3f Vector3f::Zero = Vector3f(0.0f, 0.0f, 0.0f);
const Vector3f Vector3f::One = Vector3f(1.0f, 1.0f, 1.0f);

Vector3f::Vector3f()
	: x(0.0f), y(0.0f), z(0.0f)
{
}

Vector3f::Vector3f(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

Vector3f::Vector3f(const Vector3f& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3f::~Vector3f()
{
}

float Vector3f::Length()
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

float Vector3f::Dot(const Vector3f& other)
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}

Vector3f Vector3f::Normalized()
{
	float length = Length();
	float _x = x / length;
	float _y = y / length;
	float _z = z / length;

	return Vector3f(_x, _y, _z);
}

Vector3f Vector3f::Cross(const Vector3f& other)
{
	float _x = y * other.z - z * other.y;
	float _y = -x * other.z + z * other.x;
	float _z = x * other.y - y * other.x;

	return Vector3f(_x, _y, _z);
}

Vector3f& Vector3f::operator=(const Vector3f& other)
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

std::wstring Vector3f::ToString()
{
	return std::wstring(L"(")
		+ std::to_wstring(x) + std::wstring(L", ")
		+ std::to_wstring(y) + std::wstring(L", ")
		+ std::to_wstring(z)
		+ std::wstring(L")\n");
}

Vector3f Vector3f::operator+(const Vector3f& other)
{
	return Vector3f(x + other.x, y + other.y, z + other.z);
}

Vector3f Vector3f::operator+(const float& other)
{
	return Vector3f(x + other, y + other, z + other);
}

Vector3f& Vector3f::operator+=(const Vector3f& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3f& Vector3f::operator+=(const float& other)
{
	x += other;
	y += other;
	z += other;

	return *this;
}

Vector3f Vector3f::operator-(const Vector3f& other)
{
	return Vector3f(x - other.x, y - other.y, z - other.z);
}

Vector3f Vector3f::operator-(const float& other)
{
	return Vector3f(x - other, y - other, z - other);
}

Vector3f& Vector3f::operator-=(const Vector3f& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3f& Vector3f::operator-=(const float& other)
{
	x -= other;
	y -= other;
	z -= other;

	return *this;
}

Vector3f Vector3f::operator*(const Vector3f& other)
{
	return Vector3f(x * other.x, y * other.y, z * other.z);
}

Vector3f Vector3f::operator*(const float& other)
{
	return Vector3f(x * other, y * other, z * other);
}

Vector3f& Vector3f::operator*=(const Vector3f& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

Vector3f& Vector3f::operator*=(const float& other)
{
	x *= other;
	y *= other;
	z *= other;

	return *this;
}

Vector3f Vector3f::operator/(const Vector3f& other)
{
	return Vector3f(x / other.x, y / other.y, z / other.z);
}

Vector3f Vector3f::operator/(const float& other)
{
	return Vector3f(x / other, y / other, z / other);
}

Vector3f& Vector3f::operator/=(const Vector3f& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;

	return *this;
}

Vector3f& Vector3f::operator/=(const float& other)
{
	x /= other;
	y /= other;
	z /= other;

	return *this;
}