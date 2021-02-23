#pragma once

class Vector2f
{
public:
	float x;
	float y;

	Vector2f();
	Vector2f(float x, float y);
	Vector2f(const Vector2f& other);
	~Vector2f();

	float Length();
	float Dot(const Vector2f& other);
	Vector2f Normalized();

	Vector2f& operator=(const Vector2f& other);

	Vector2f& operator+(const Vector2f& other);
	Vector2f& operator+(const float& other);
	Vector2f& operator+=(const Vector2f& other);
	Vector2f& operator+=(const float& other);

	Vector2f& operator-(const Vector2f& other);
	Vector2f& operator-(const float& other);
	Vector2f& operator-=(const Vector2f& other);
	Vector2f& operator-=(const float& other);

	Vector2f& operator*(const Vector2f& other);
	Vector2f& operator*(const float& other);
	Vector2f& operator*=(const Vector2f& other);
	Vector2f& operator*=(const float& other);

	Vector2f& operator/(const Vector2f& other);
	Vector2f& operator/(const float& other);
	Vector2f& operator/=(const Vector2f& other);
	Vector2f& operator/=(const float& other);
};