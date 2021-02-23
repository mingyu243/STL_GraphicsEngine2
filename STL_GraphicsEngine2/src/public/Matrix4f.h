#pragma once

#include "Vector3f.h"

class Matrix4f
{
public:
	Matrix4f();
	~Matrix4f();

	static Matrix4f Identity();
	static Matrix4f Translation(Vector3f position);
	static Matrix4f Translation(float x, float y, float z);
	static Matrix4f Rotation(Vector3f rotation);
	static Matrix4f Rotation(float x, float y, float z);
	static Matrix4f RotationX(float angle);
	static Matrix4f RotationY(float angle);
	static Matrix4f RotationZ(float angle);

	static Matrix4f Scale(Vector3f scale);
	static Matrix4f Scale(float x, float y, float z);
	static Matrix4f LookAt(Vector3f position, Vector3f target, Vector3f up);
	static Matrix4f Perspective(float fov, float width, float height, float zNear, float zFar);
	static Matrix4f Transpose(const Matrix4f& target);

	float& Get(int row, int col);
	float* GetM();

	Matrix4f& operator=(const Matrix4f other);
	Matrix4f operator*(const Matrix4f other);
	Matrix4f operator*=(const Matrix4f other);

	Vector3f operator*(const Vector3f other);

	static const unsigned int elementSize = 4 * 4;

private:
	float elements[elementSize];
};