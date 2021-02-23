#pragma once

#include <string>

class Vector3f
{
public:
	float x;
	float y;
	float z;

	static const Vector3f Right;
	static const Vector3f Forward;
	static const Vector3f Up;
	static const Vector3f Zero;
	static const Vector3f One;

	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f& other);
	~Vector3f();

	std::wstring ToString();

	float Length();
	float Dot(const Vector3f& other);
	Vector3f Normalized();
	Vector3f Cross(const Vector3f& other);

	Vector3f& operator=(const Vector3f& other);

	Vector3f operator+(const Vector3f& other);
	Vector3f operator+(const float& other);
	Vector3f& operator+=(const Vector3f& other);
	Vector3f& operator+=(const float& other);

	Vector3f operator-(const Vector3f& other);
	Vector3f operator-(const float& other);
	Vector3f& operator-=(const Vector3f& other);
	Vector3f& operator-=(const float& other);

	Vector3f operator*(const Vector3f& other);
	Vector3f operator*(const float& other);
	Vector3f& operator*=(const Vector3f& other);
	Vector3f& operator*=(const float& other);

	Vector3f operator/(const Vector3f& other);
	Vector3f operator/(const float& other);
	Vector3f& operator/=(const Vector3f& other);
	Vector3f& operator/=(const float& other);
};