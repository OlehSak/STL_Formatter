#include <vector>

class Calculations
{
private:
	double	vectorMultiple(
		double x1, double y1, double z1,
		double x2, double y2, double z2);
	double	vectorLength(double x, double y, double z);

public:
	Calculations();
	~Calculations();

	double	getSpace(
		std::vector<double> vertex0,
		std::vector<double> vertex1,
		std::vector<double> vertex2);
	double	angleCalculetion(
		double x1, double y1, double z1,
		double x2, double y2, double z2);

};