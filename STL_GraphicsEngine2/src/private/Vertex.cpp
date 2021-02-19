#include "../public/Vertex.h"

Vertex::Vertex()
	: Vertex(0.0f, 0.0f, 0.0f)
{
}

Vertex::Vertex(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

Vertex::~Vertex()
{
}
