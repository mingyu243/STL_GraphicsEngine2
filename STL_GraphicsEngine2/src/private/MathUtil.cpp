#include "MathUtil.h"

void MathUtil::Swapf(float& left, float& right)
{
	float temp = left;
	left = right;
	right = temp;
}