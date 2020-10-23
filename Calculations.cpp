#include "Calculations.h"

Calculations::Calculations(void)
{}

Calculations::~Calculations(void)
{}

double	Calculations::vectorMultiple(double x1, double y1, double z1, double x2, double y2, double z2)
{
	return x1 * x2 + y1 * y2 + z1 * z2;
}

double	Calculations::vectorLength(double x, double y, double z)
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

double	Calculations::angleCalculetion(double x1, double y1, double z1, double x2, double y2, double z2)
{
	const double PI = 3.141592653589793238463;
	double mul;
	double length1;
	double length2;

	mul = vectorMultiple(x1, y1, z1, x2, y2, z2);
	length1 = vectorLength(x1, y1, z1);
	length2 = vectorLength(x2, y2, z2);

	return ((acos(mul / (length1 * length2)) * 180) / PI);
}

double	Calculations::getSpace(
	std::vector<double> vertex0,
	std::vector<double> vertex1,
	std::vector<double> vertex2)
{
	std::vector<double>	ABxAC(3);
	double	mod;

	std::vector<double> VectorAB{
		vertex1.at(0) - vertex0.at(0),
		vertex1.at(1) - vertex0.at(1),
		vertex1.at(2) - vertex0.at(2) };

	std::vector<double> VectorAC{
		vertex2.at(0) - vertex0.at(0),
		vertex2.at(1) - vertex0.at(1),
		vertex2.at(2) - vertex0.at(2) };

	ABxAC.at(0) = VectorAB.at(1) * VectorAC.at(2) - VectorAB.at(2) * VectorAC.at(1);
	ABxAC.at(1) = VectorAB.at(2) * VectorAC.at(0) - VectorAB.at(0) * VectorAC.at(2);
	ABxAC.at(2) = VectorAB.at(0) * VectorAC.at(1) - VectorAB.at(1) * VectorAC.at(0);

	mod = sqrt(pow(ABxAC.at(0), 2) + pow(ABxAC.at(1), 2) + pow(ABxAC.at(2), 2));

	return mod / 2;
}