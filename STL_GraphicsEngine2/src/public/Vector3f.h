#pragma once

#include <math.h>

class Vector3f
{
public:
	float x;
	float y;
	float z;

	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f& other); // 복사 생성자.
	~Vector3f();

	float Length();								// 벡터 길이.
	Vector3f Add(const Vector3f& other);		// 더하기.
	Vector3f Substract(const Vector3f& other);	// 빼기.
	//float Dot(const Vector3f& other);			// 내적.
	//float Normalized();						// 단위 벡터. (정규화.)

	Vector3f& operator=(const Vector3f& other);
	Vector3f operator+(const Vector3f& other);
	Vector3f operator-(const Vector3f& other);
};