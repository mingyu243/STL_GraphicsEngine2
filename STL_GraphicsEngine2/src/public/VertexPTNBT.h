#pragma once

#include "Vector2f.h"
#include "Vector3f.h"

class VertexPTNBT
{
public:
	Vector3f position;
	Vector2f uv;
	Vector3f normal;
	Vector3f binormal;
	Vector3f tangent;

	VertexPTNBT() = default;
	VertexPTNBT(Vector3f position, Vector2f uv, Vector3f normal, Vector3f binormal, Vector3f tangent);
	VertexPTNBT(const VertexPTNBT& other);
	VertexPTNBT& operator=(const VertexPTNBT& other);
	~VertexPTNBT() = default;
};

