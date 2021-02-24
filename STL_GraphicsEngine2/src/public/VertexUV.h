#pragma once

#include "Vector2f.h"
#include "Vector3f.h"

class VertexUV
{
public:
	float x;
	float y;
	float z;

	float u;
	float v;

	VertexUV();
	VertexUV(float x, float y, float z);
	VertexUV(float x, float y, float z, float u, float v);
	VertexUV(Vector3f position);
	VertexUV(Vector3f position, Vector2f uv);
	VertexUV(const VertexUV& other);
	~VertexUV();

	VertexUV& operator=(const VertexUV& other);
};

