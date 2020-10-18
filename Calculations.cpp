#include "Header.h"

double	vectorMultiple(double x1, double y1, double z1, double x2, double y2, double z2)
{
	return x1 * x2 + y1 * y2 + z1 * z2;
}

double	vectorLength(double x, double y, double z)
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

double	angleCalculetion(double x1, double y1, double z1, double x2, double y2, double z2)
{
	const double PI = 3.141592653589793238463;
	double mul;
	double length1;
	double length2;

	mul = vectorMultiple(x1, y1, z1, x2, y2, z2);
	length1 = vectorLength(x1, y1, z1);
	length2 = vectorLength(x2, y2, z2);

	return ((acos(mul / (length1 * length2)) * 180) / PI);// -90;
}

double	getSpace(
	std::vector<double> vertex0,
	std::vector<double> vertex1,
	std::vector<double> vertex2)
{
	double	VectorAB[3];
	double	VectorAC[3];
	double	ABxAC[3];

	double	mod;

	VectorAB[0] = vertex1[0] - vertex0[0];
	VectorAB[1] = vertex1[1] - vertex0[1];
	VectorAB[2] = vertex1[2] - vertex0[2];

	VectorAC[0] = vertex2[0] - vertex0[0];
	VectorAC[1] = vertex2[1] - vertex0[1];
	VectorAC[2] = vertex2[2] - vertex0[2];

	ABxAC[0] = VectorAB[1] * VectorAC[2] - VectorAB[2] * VectorAC[1];
	ABxAC[1] = VectorAB[2] * VectorAC[0] - VectorAB[0] * VectorAC[2];
	ABxAC[2] = VectorAB[0] * VectorAC[1] - VectorAB[1] * VectorAC[0];

	mod = sqrt(pow(ABxAC[0], 2) + pow(ABxAC[1], 2) + pow(ABxAC[2], 2));

	return mod / 2;
}