#pragma once
class Vertex
{
public:
	// Getter Setter 하는 게 맞는데, 편하게 쓰려고 그냥 이렇게 했음.
	float x;
	float y;
	float z;
	
	Vertex();
	Vertex(float x, float y, float z);
	~Vertex();
};

