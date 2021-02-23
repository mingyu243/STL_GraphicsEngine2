#pragma once

class MathUtil
{
public:
	static constexpr float PI = 3.14159265f;
	static constexpr float Deg2Rad = (PI / 180.0f);
	static constexpr float Rad2Deg = (180.0f / PI);
	static void Swapf(float& left, float& right);
};