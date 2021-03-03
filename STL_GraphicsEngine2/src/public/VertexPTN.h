#pragma once

#include "Vector3f.h"
#include "Vector2f.h"

class VertexPTN
{
public:
	Vector3f position;
	Vector2f uv;
	Vector3f normal;

	VertexPTN() = default;
	VertexPTN(Vector3f position, Vector2f uv, Vector3f normal);
	VertexPTN(const VertexPTN& other);
	VertexPTN& operator=(const VertexPTN& other);

	~VertexPTN() = default;
};

