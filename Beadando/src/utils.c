#include "utils.h"

#include <math.h>

double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}

float radian_to_degree(float rad)
{
	return rad * 180.0 / M_PI;
}
