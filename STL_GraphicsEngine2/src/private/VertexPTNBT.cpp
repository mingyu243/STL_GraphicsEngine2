#include "VertexPTNBT.h"

VertexPTNBT::VertexPTNBT(Vector3f position, Vector2f uv, Vector3f normal, Vector3f binormal, Vector3f tangent)
	: position(position), uv(uv), normal(normal), binormal(binormal), tangent(tangent)
{
}

VertexPTNBT::VertexPTNBT(const VertexPTNBT& other)
	:VertexPTNBT(other.position, other.uv, other.normal, other.binormal, other.tangent)
{
}

VertexPTNBT& VertexPTNBT::operator=(const VertexPTNBT& other)
{
	position = other.position;
	uv = other.uv;
	normal = other.normal;
	binormal = other.binormal;
	tangent = other.tangent;

	return *this;
}
