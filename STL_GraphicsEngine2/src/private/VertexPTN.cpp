#include "VertexPTN.h"

VertexPTN::VertexPTN(Vector3f position, Vector2f uv, Vector3f normal)
	: position(position), uv(uv), normal(normal)
{

}

VertexPTN::VertexPTN(const VertexPTN& other)
	: VertexPTN(other.position, other.uv, other.normal)
{
}

VertexPTN& VertexPTN::operator=(const VertexPTN& other)
{
	position = other.position;
	uv = other.uv;
	normal = other.normal;

	return *this;
}
