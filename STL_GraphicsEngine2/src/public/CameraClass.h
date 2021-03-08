#pragma once

#include "Matrix4f.h"
#include "Vector3f.h"
#include <d3d11.h>

#include <wrl.h>
using Microsoft::WRL::ComPtr; // Com 객체를 간접적으로 New, Delete 하는 용도. DirectX가 Com 객체를 쓰기 때문에 이거를 씀.

class CameraBufferData
{
public:
	Matrix4f viewProjection;
	Vector3f cameraPosition;
	float pad1_Time;

	CameraBufferData() = default;
	~CameraBufferData() = default;
};

// 뷰 변환. / 투영 변환.
class Camera
{
public:
	Camera();
	Camera(float fov, float width, float height, float zNear, float zFar);
	Camera(Camera& other);
	~Camera() = default;

	// 이동/회전.
	void MoveForward(float velocity);
	void MoveRight(float velocity);
	void MoveUp(float velocity);

	// Y축 회전.
	void Yaw(float angle);
	// X축 회전.
	void Pitch(float angle);

	// 상수 버퍼 생성/바인딩.
	bool CreateBuffer(ID3D11Device* device);
	void BindBuffer(ID3D11DeviceContext* deviceContext);

	// Getter / Setter.
	// 종횡비.
	float AspectRatio() { return (float)width / (float)height; }
	void SetAspectRatio(float width, float height);
	
	Matrix4f View() { return viewMatrix; }
	Matrix4f Projection() { return projectionMatrix; }

	Vector3f Position() { return position; }
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3f position);

	void UpdateCamera();

private:
	// 투영 변환 관련 변수.
	float fov;						// Field Of View(시야각).
	float width;					// 화면 너비. (ex: 1280)
	float height;					// 화면 높이. (ex: 800)
	float zNear;					// 프러스텀 z 가까운 위치.
	float zFar;						// 프러스텀 z 먼 위치.

	Matrix4f projectionMatrix;

	// 뷰 변환 관련 변수.
	float yaw = 0.0f;				// Y축 회전 값.
	float pitch = 0.0f;				// X축 회전 값.
	
	Vector3f position;				// 카메라 위치.

	Vector3f forward;				// 앞방향.
	Vector3f right;					// 오른쪽.
	Vector3f up;					// 위.

	Vector3f look;					// 바라보는 위치.

	Matrix4f viewMatrix;			// 뷰(카메라) 행렬.

	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

	// 상수 버퍼 - 뷰/투영 행렬 전달용 버퍼.
	ComPtr<ID3D11Buffer> cameraBuffer;
};