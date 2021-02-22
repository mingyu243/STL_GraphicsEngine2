#include "Vector3f.h"

Vector3f::Vector3f()
	: x(0.0f), y(0.0f), z(0.0f)
{
}

Vector3f::Vector3f(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

// 복사 생성자.
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

Vector3f Vector3f::Add(const Vector3f& other)
{
	Vector3f result;
	result.x = x + other.x;
	result.y = y + other.y;
	result.z = z + other.z;

	return result;
}

Vector3f Vector3f::Substract(const Vector3f& other)
{
	Vector3f result;
	result.x = x - other.x;
	result.y = y - other.y;
	result.z = z - other.z;

	return result;
}

Vector3f& Vector3f::operator=(const Vector3f& other)
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

Vector3f Vector3f::operator+(const Vector3f& other)
{
	return Vector3f(Add(other));
}

Vector3f Vector3f::operator-(const Vector3f& other)
{
	return Vector3f(Substract(other));
}
