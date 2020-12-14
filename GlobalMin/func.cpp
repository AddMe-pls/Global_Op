#include <cmath>
#include <iostream>
#include <math.h>
#include <vector>
#include "header.h"

double f(double x)
{
	return (x * x + sin(x));
}

double LipshConst(double x2, double x1, double z2, double z1)
{
	return (abs(z2 - z1) / (x2 - x1));
}

/*bool func(double x1, double x2)
{
	if (x1 < x2)
		return true;
	else return false;
}*/