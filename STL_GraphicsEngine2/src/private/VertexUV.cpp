#include "Vertex.h"
#include "..\public\VertexUV.h"

VertexUV::VertexUV()
	:VertexUV(0.0f, 0.0f, 0.0f, 0.0f, 0.0f)
{
}

VertexUV::VertexUV(float x, float y, float z)
	:VertexUV(x, y, z, 0.0f, 0.0f)
{
}

VertexUV::VertexUV(float x, float y, float z, float u, float v)
	:x(x), y(y), z(z), u(u), v(v)
{
}

VertexUV::VertexUV(Vector3f position)
	:VertexUV(position.x, position.y, position.z, 0.0f, 0.0f)
{
}

VertexUV::VertexUV(Vector3f position, Vector2f uv)
	:VertexUV(position.x, position.y, position.z, uv.x, uv.y)
{
}

VertexUV::VertexUV(const VertexUV& other)
	:VertexUV(other.x, other.y, other.z, other.u, other.v)
{
}

VertexUV::~VertexUV()
{
}

VertexUV& VertexUV::operator=(const VertexUV& other)
{
	x = other.x;
	y = other.y;
	z = other.z;

	u = other.u;
	v = other.v;

	return *this;
}
