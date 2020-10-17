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
		std::vector<double> vertex0;
		std::vector<double> vertex1;
		std::vector<double> vertex2;

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
				//std::cout << "SPLITED FACET:" << splited.size() << ' ' << splited[4] << std::endl;

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