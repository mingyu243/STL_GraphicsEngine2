#include "Matrix4f.h"

#include <Windows.h>

#include <math.h>
#include "MathUtil.h"

Matrix4f::Matrix4f()
{
	memset(elements, 0, sizeof(elements));
}

Matrix4f::~Matrix4f()
{
}

Matrix4f Matrix4f::Identity()
{
	Matrix4f identity;
	identity.Get(0, 0) = 1.0f;  identity.Get(0, 1) = 0.0f;  identity.Get(0, 2) = 0.0f;  identity.Get(0, 3) = 0.0f;
	identity.Get(1, 0) = 0.0f;  identity.Get(1, 1) = 1.0f;  identity.Get(1, 2) = 0.0f;  identity.Get(1, 3) = 0.0f;
	identity.Get(2, 0) = 0.0f;  identity.Get(2, 1) = 0.0f;  identity.Get(2, 2) = 1.0f;  identity.Get(2, 3) = 0.0f;
	identity.Get(3, 0) = 0.0f;  identity.Get(3, 1) = 0.0f;  identity.Get(3, 2) = 0.0f;  identity.Get(3, 3) = 1.0f;

	return identity;
}

Matrix4f Matrix4f::Translation(Vector3f position)
{
	return Matrix4f::Translation(position.x, position.y, position.z);
}

Matrix4f Matrix4f::Translation(float x, float y, float z)
{
	Matrix4f result;
	result.Get(0, 0) = 1.0f;  result.Get(0, 1) = 0.0f;  result.Get(0, 2) = 0.0f;  result.Get(0, 3) = 0.0f;
	result.Get(1, 0) = 0.0f;  result.Get(1, 1) = 1.0f;  result.Get(1, 2) = 0.0f;  result.Get(1, 3) = 0.0f;
	result.Get(2, 0) = 0.0f;  result.Get(2, 1) = 0.0f;  result.Get(2, 2) = 1.0f;  result.Get(2, 3) = 0.0f;
	result.Get(3, 0) = x;  result.Get(3, 1) = y;	result.Get(3, 2) = z;  result.Get(3, 3) = 1.0f;

	return result;
}

Matrix4f Matrix4f::Rotation(Vector3f rotation)
{
	return Matrix4f::Rotation(rotation.x, rotation.y, rotation.z);
}

Matrix4f Matrix4f::Rotation(float x, float y, float z)
{
	return RotationY(y) * RotationX(x) * RotationZ(z);
}

Matrix4f Matrix4f::RotationX(float angle)
{
	Matrix4f rx;

	angle *= MathUtil::Deg2Rad;

	float cosX = cosf(angle);
	float sinX = sinf(angle);

	rx.Get(0, 0) = 1.0f;  rx.Get(0, 1) = 0.0f;  rx.Get(0, 2) = 0.0f;   rx.Get(0, 3) = 0.0f;
	rx.Get(1, 0) = 0.0f;  rx.Get(1, 1) = cosX;  rx.Get(1, 2) = -sinX;  rx.Get(1, 3) = 0.0f;
	rx.Get(2, 0) = 0.0f;  rx.Get(2, 1) = sinX;  rx.Get(2, 2) = cosX;   rx.Get(2, 3) = 0.0f;
	rx.Get(3, 0) = 0.0f;  rx.Get(3, 1) = 0.0f;  rx.Get(3, 2) = 0.0f;   rx.Get(3, 3) = 1.0f;

	return rx;
}

Matrix4f Matrix4f::RotationY(float angle)
{
	Matrix4f ry;

	angle *= MathUtil::Deg2Rad;

	float cosY = cosf(angle);
	float sinY = sinf(angle);

	ry.Get(0, 0) = cosY;	ry.Get(0, 1) = 0.0f;  ry.Get(0, 2) = sinY;	 ry.Get(0, 3) = 0.0f;
	ry.Get(1, 0) = 0.0f;	ry.Get(1, 1) = 1.0f;  ry.Get(1, 2) = 0.0f;   ry.Get(1, 3) = 0.0f;
	ry.Get(2, 0) = -sinY;	ry.Get(2, 1) = 0.0f;  ry.Get(2, 2) = cosY;   ry.Get(2, 3) = 0.0f;
	ry.Get(3, 0) = 0.0f;	ry.Get(3, 1) = 0.0f;  ry.Get(3, 2) = 0.0f;   ry.Get(3, 3) = 1.0f;

	return ry;
}

Matrix4f Matrix4f::RotationZ(float angle)
{
	Matrix4f rz;

	angle *= MathUtil::Deg2Rad;

	float cosZ = cosf(angle);
	float sinZ = sinf(angle);

	rz.Get(0, 0) = cosZ;  rz.Get(0, 1) = -sinZ;  rz.Get(0, 2) = 0.0f;  rz.Get(0, 3) = 0.0f;
	rz.Get(1, 0) = sinZ;  rz.Get(1, 1) = cosZ;   rz.Get(1, 2) = 0.0f;  rz.Get(1, 3) = 0.0f;
	rz.Get(2, 0) = 0.0f;  rz.Get(2, 1) = 0.0f;   rz.Get(2, 2) = 1.0f;  rz.Get(2, 3) = 0.0f;
	rz.Get(3, 0) = 0.0f;  rz.Get(3, 1) = 0.0f;   rz.Get(3, 2) = 0.0f;  rz.Get(3, 3) = 1.0f;

	return rz;
}

Matrix4f Matrix4f::Scale(Vector3f scale)
{
	return Matrix4f::Scale(scale.x, scale.y, scale.z);
}

Matrix4f Matrix4f::Scale(float x, float y, float z)
{
	Matrix4f result;
	result.Get(0, 0) = x;     result.Get(0, 1) = 0.0f;  result.Get(0, 2) = 0.0f;  result.Get(0, 3) = 0.0f;
	result.Get(1, 0) = 0.0f;  result.Get(1, 1) = y;     result.Get(1, 2) = 0.0f;  result.Get(1, 3) = 0.0f;
	result.Get(2, 0) = 0.0f;  result.Get(2, 1) = 0.0f;  result.Get(2, 2) = z;     result.Get(2, 3) = 0.0f;
	result.Get(3, 0) = 0.0f;  result.Get(3, 1) = 0.0f;  result.Get(3, 2) = 0.0f;  result.Get(3, 3) = 1.0f;

	return result;
}

Matrix4f Matrix4f::LookAt(Vector3f position, Vector3f target, Vector3f up)
{
	Vector3f forward = (target - position).Normalized();
	Vector3f right = up.Cross(forward).Normalized();
	Vector3f upDir = forward.Cross(right).Normalized();

	float x = right.Dot(position);
	float y = upDir.Dot(position);
	float z = forward.Dot(position);

	Matrix4f result;
	result.Get(0, 0) = right.x;	    result.Get(0, 1) = upDir.x;	    result.Get(0, 2) = forward.x;	result.Get(0, 3) = 0.0f;
	result.Get(1, 0) = right.y;	    result.Get(1, 1) = upDir.y;	    result.Get(1, 2) = forward.y;	result.Get(1, 3) = 0.0f;
	result.Get(2, 0) = right.z;		result.Get(2, 1) = upDir.z;		result.Get(2, 2) = forward.z;	result.Get(2, 3) = 0.0f;
	result.Get(3, 0) = -x;			result.Get(3, 1) = -y;			result.Get(3, 2) = -z;			result.Get(3, 3) = 1.0f;

	return result;
}

Matrix4f Matrix4f::Perspective(float fov, float width, float height, float zNear, float zFar)
{
	float aspect = width / height;
	float radians = fov / 2.0f;

	float H = 1 / tanf(radians);
	float W = H / aspect;
	float A = zFar / (zFar - zNear);
	float B = (-zNear * zFar) / (zFar - zNear);

	Matrix4f result;
	result.Get(0, 0) = W;		result.Get(0, 1) = 0.0f;	result.Get(0, 2) = 0.0f;	result.Get(0, 3) = 0.0f;
	result.Get(1, 0) = 0.0f;	result.Get(1, 1) = H;	    result.Get(1, 2) = 0.0f;	result.Get(1, 3) = 0.0f;
	result.Get(2, 0) = 0.0f;	result.Get(2, 1) = 0.0f;	result.Get(2, 2) = A;       result.Get(2, 3) = 1.0f;
	result.Get(3, 0) = 0.0f;	result.Get(3, 1) = 0.0f;	result.Get(3, 2) = B;		result.Get(3, 3) = 0.0f;

	return result;
}

Matrix4f Matrix4f::Transpose(const Matrix4f& target)
{
	Matrix4f result = target;

	MathUtil::Swapf(result.Get(0, 1), result.Get(1, 0));
	MathUtil::Swapf(result.Get(0, 2), result.Get(2, 0));
	MathUtil::Swapf(result.Get(0, 3), result.Get(3, 0));

	MathUtil::Swapf(result.Get(1, 2), result.Get(2, 1));
	MathUtil::Swapf(result.Get(1, 3), result.Get(3, 1));
	MathUtil::Swapf(result.Get(2, 3), result.Get(3, 2));

	return result;
}

float& Matrix4f::Get(int row, int col)
{
	return elements[row + (col * 4)];
}

float* Matrix4f::GetM()
{
	return elements;
}

Matrix4f& Matrix4f::operator=(const Matrix4f other)
{
	for (int ix = 0; ix < elementSize; ++ix)
	{
		elements[ix] = other.elements[ix];
	}

	return *this;
}

Matrix4f Matrix4f::operator*(const Matrix4f other)
{
	Matrix4f result;
	for (int ix = 0; ix < 4; ++ix)
	{
		result.Get(ix, 0) =
			Get(ix, 0) * other.elements[0 + 0 * 4] +
			Get(ix, 1) * other.elements[1 + 0 * 4] +
			Get(ix, 2) * other.elements[2 + 0 * 4] +
			Get(ix, 3) * other.elements[3 + 0 * 4];

		result.Get(ix, 1) =
			Get(ix, 0) * other.elements[0 + 1 * 4] +
			Get(ix, 1) * other.elements[1 + 1 * 4] +
			Get(ix, 2) * other.elements[2 + 1 * 4] +
			Get(ix, 3) * other.elements[3 + 1 * 4];

		result.Get(ix, 2) =
			Get(ix, 0) * other.elements[0 + 2 * 4] +
			Get(ix, 1) * other.elements[1 + 2 * 4] +
			Get(ix, 2) * other.elements[2 + 2 * 4] +
			Get(ix, 3) * other.elements[3 + 2 * 4];

		result.Get(ix, 3) =
			Get(ix, 0) * other.elements[0 + 3 * 4] +
			Get(ix, 1) * other.elements[1 + 3 * 4] +
			Get(ix, 2) * other.elements[2 + 3 * 4] +
			Get(ix, 3) * other.elements[3 + 3 * 4];
	}

	return result;
}

Matrix4f Matrix4f::operator*=(const Matrix4f other)
{
	*this = *this * other;
	return *this;
}

Vector3f Matrix4f::operator*(const Vector3f other)
{
	Vector3f result;
	result.x = elements[0] * other.x + elements[4] * other.y + elements[8] * other.z;
	result.y = elements[1] * other.x + elements[5] * other.y + elements[9] * other.z;
	result.z = elements[2] * other.x + elements[6] * other.y + elements[10] * other.z;

	return result;
}