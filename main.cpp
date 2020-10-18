#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		if(token.length() > 0)
			tokens.push_back(token);
	}
	return tokens;
}

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

	return ((acos(mul / (length1 * length2)) * 180) / PI) - 90;
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

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		std::cout << argv[1] << std::endl;

		long int countOfTriangle;
		std::size_t found;

		std::string		str;
		std::ifstream	file(argv[1]);
		std::vector<std::string>	splited_arr[3];
		std::vector<std::string>	splited;
		double space;
		double sum;
		std::vector<double> facet;

		std::vector<double> vertex0;
		std::vector<double> vertex1;
		std::vector<double> vertex2;

		facet.resize(3);
		vertex0.resize(3);
		vertex1.resize(3);
		vertex2.resize(3);

		sum = 0;
		countOfTriangle = 0;
		while(std::getline(file, str))
		{
			std::string key("facet normal");
			found = str.rfind(key);
			if (found != std::string::npos)
			{
				splited = split(str, ' ');
				std::cout << "SPLITED FACET:" << splited.size() << ' ' << splited[4] << std::endl;

				facet.at(0) = stod(splited[splited.size() - 3]);
				facet.at(1) = stod(splited[splited.size() - 2]);
				facet.at(2) = stod(splited[splited.size() - 1]);

				double angle = angleCalculetion(facet[0], facet[1], facet[2], 0, 0, 1);
				std::cout << "ANGLE in DEGREES:" << angle << std::endl;

				std::getline(file, str);
				std::string key("outer loop");
				found = str.rfind(key);
				if (found != std::string::npos)
				{
					std::string		str[3];

					std::getline(file, str[0]);
					splited_arr[0] = split(str[0], ' ');

					vertex0.at(0) = stod(splited_arr[0][splited_arr[0].size() - 3]);
					vertex0.at(1) = stod(splited_arr[0][splited_arr[0].size() - 2]);
					vertex0.at(2) = stod(splited_arr[0][splited_arr[0].size() - 1]);

					//std::cout << "SPLITED V1:" << splited_arr[0].size() << std::endl;
					//std::cout << stod(splited_arr[0][splited_arr[0].size() - 3]) << std::endl;
					//std::cout << stod(splited_arr[0][splited_arr[0].size() - 2]) << std::endl;
					//std::cout << stod(splited_arr[0][splited_arr[0].size() - 1]) << std::endl;

					std::getline(file, str[1]);
					splited_arr[1] = split(str[1], ' ');

					vertex1.at(0) = stod(splited_arr[1][splited_arr[1].size() - 3]);
					vertex1.at(1) = stod(splited_arr[1][splited_arr[1].size() - 2]);
					vertex1.at(2) = stod(splited_arr[1][splited_arr[1].size() - 1]);

					/*std::cout << "SPLITED V2:" << splited_arr[1].size() << std::endl;
					std::cout << splited_arr[1][splited_arr[1].size() - 3] << std::endl;
					std::cout << splited_arr[1][splited_arr[1].size() - 2] << std::endl;
					std::cout << splited_arr[1][splited_arr[1].size() - 1] << std::endl;*/

					std::getline(file, str[2]);
					splited_arr[2] = split(str[2], ' ');

					vertex2.at(0) = stod(splited_arr[2][splited_arr[2].size() - 3]);
					vertex2.at(1) = stod(splited_arr[2][splited_arr[2].size() - 2]);
					vertex2.at(2) = stod(splited_arr[2][splited_arr[2].size() - 1]);

					/*std::cout << "SPLITED V3:" << splited_arr[2].size() << std::endl;
					std::cout << splited_arr[2][splited_arr[2].size() - 3] << std::endl;
					std::cout << splited_arr[2][splited_arr[2].size() - 2] << std::endl;
					std::cout << splited_arr[2][splited_arr[2].size() - 1] << std::endl;*/

					space = getSpace(vertex0, vertex1, vertex2);
					sum += space;
					std::cout << "SPACEEEEE: " << space << std::endl;
				}

				//std::cout << splited[0][4] << '\n' << splited[1][4] << '\n' << splited[2][4] << '\n' << std::endl;

				countOfTriangle += 1;
			}

			//std::cout << space.getSpace() << std::endl;
			str.clear();
		}
		std::cout << "SUM: " << sum << std::endl;
		std::cout << "COUNT OF TRIANGLE: " << countOfTriangle << '\n';
		file.close();
	}
	else
	{
		std::cout << "not arguments" << std::endl;
	}
	return (0);
}