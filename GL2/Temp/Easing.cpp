#include "Easing.h"


float linear_easing(float time, float period, float begin, float end)
{
	return ((end - begin) / period) * time + begin;
}

