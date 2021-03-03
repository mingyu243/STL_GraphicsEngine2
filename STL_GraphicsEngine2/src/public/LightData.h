#pragma once

#include "Vector3f.h"

class LightData
{
public:
	Vector3f position;
	float pad1;

	LightData() = default;
	~LightData() = default;
};

