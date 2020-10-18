#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <SDL.h>

std::vector<std::string> split(const std::string& s, char delimiter);
double	vectorMultiple(double x1, double y1, double z1, double x2, double y2, double z2);
double	vectorLength(double x, double y, double z);
double	angleCalculetion(double x1, double y1, double z1, double x2, double y2, double z2);
double	getSpace(
	std::vector<double> vertex0,
	std::vector<double> vertex1,
	std::vector<double> vertex2);

int	render(std::vector<double> array_of_space, double maxSpace);
