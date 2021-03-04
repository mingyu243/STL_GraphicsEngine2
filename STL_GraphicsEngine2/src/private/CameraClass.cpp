#include "CameraClass.h"

Camera::Camera()
	: Camera(70.0f, 1280.0f, 800.0f, 0.1f, 1000.0f)
{
}

Camera::Camera(float fov, float width, float height, float zNear, float zFar)
	: fov(fov), width(width), height(height), zNear(zNear), zFar(zFar),
	position(0.0f, 0.0f, -5.0f),
	look(0.0f, 0.0f, 0.0f),
	up(0.0f, 1.0f, 0.0f),
	right(1.0f, 0.0f, 0.0f),
	forward(0.0f, 0.0f, 1.0f)
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

Camera::Camera(Camera& other)
	: Camera(other.fov, other.width, other.height, other.zNear, other.zFar)
{
}

void Camera::MoveForward(float velocity)
{
	position += forward * velocity;
}

void Camera::MoveRight(float velocity)
{
	position += right * velocity;
}

void Camera::MoveUp(float velocity)
{
	position += up * velocity;
}

void Camera::Yaw(float angle)
{
	yaw += angle;
}

void Camera::Pitch(float angle)
{
	pitch += angle;
}

bool Camera::CreateBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC cameraBufferDesc;
	memset(&cameraBufferDesc, 0, sizeof(cameraBufferDesc));
	cameraBufferDesc.ByteWidth = sizeof(CameraBufferData);
	cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	cameraBufferDesc.CPUAccessFlags = 0;
	cameraBufferDesc.MiscFlags = 0;

	CameraBufferData cameraData;
	cameraData.viewProjection = viewMatrix * projectionMatrix;
	cameraData.cameraPosition = position;

	D3D11_SUBRESOURCE_DATA data;
	memset(&data, 0, sizeof(data));
	data.pSysMem = &cameraData;

	HRESULT result = device->CreateBuffer(
		&cameraBufferDesc,
		&data,
		cameraBuffer.GetAddressOf()
	);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"카메라 버퍼 생성 실패", L"오류", 0);
		throw std::exception("카메라 버퍼 생성 실패");
		return false;
	}

	return true;
}

void Camera::BindBuffer(ID3D11DeviceContext* deviceContext)
{
	CameraBufferData cameraData;
	cameraData.viewProjection = viewMatrix * projectionMatrix;
	cameraData.cameraPosition = position;

	deviceContext->UpdateSubresource(cameraBuffer.Get(), NULL, nullptr, &cameraData, 0, 0);
	deviceContext->VSSetConstantBuffers(1, 1, cameraBuffer.GetAddressOf());
}

void Camera::SetAspectRatio(float width, float height)
{
	this->width = width;
	this->height = height;
}

void Camera::SetPosition(float x, float y, float z)
{
	this->position = Vector3f(x, y, z);
	UpdateViewMatrix();
}

void Camera::SetPosition(Vector3f position)
{
	this->position = position;
	UpdateViewMatrix();
}

void Camera::UpdateCamera()
{
	Matrix4f rotationMatrix = Matrix4f::Rotation(pitch, yaw, 0.0f);

	// 카메라가 바라봐야하는 위치 조정.
	look = rotationMatrix * Vector3f::Forward;
	look = look.Normalized();	// 정규화.
	
	// 3인칭 카메라.
	right = rotationMatrix * Vector3f::Right;
	up = rotationMatrix * Vector3f::Up;
	forward = rotationMatrix * Vector3f::Forward;

	// 바라봐야하는 위치 조정.
	look = position + look;
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	// 뷰 변환 행렬 만들기.
	viewMatrix = Matrix4f::LookAt(position, look, up);
}

void Camera::UpdateProjectionMatrix()
{
	// 투영 변환 행렬 만들기.
	projectionMatrix = Matrix4f::Perspective(fov, width, height, zNear, zFar);
}
