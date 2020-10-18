#include "Header.h"

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

		std::vector<double> array_of_space;

		double min = 90;
		double max = 0;
		double maxSpace = 0;

		array_of_space.resize(181);
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

				if (round(angle) > max)
					max = round(angle);
				if (round(angle) < min)
					min = round(angle);

				std::cout << "ANGLE in DEGREES:" << round(angle) << std::endl;

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

					std::getline(file, str[1]);
					splited_arr[1] = split(str[1], ' ');

					vertex1.at(0) = stod(splited_arr[1][splited_arr[1].size() - 3]);
					vertex1.at(1) = stod(splited_arr[1][splited_arr[1].size() - 2]);
					vertex1.at(2) = stod(splited_arr[1][splited_arr[1].size() - 1]);

					std::getline(file, str[2]);
					splited_arr[2] = split(str[2], ' ');

					vertex2.at(0) = stod(splited_arr[2][splited_arr[2].size() - 3]);
					vertex2.at(1) = stod(splited_arr[2][splited_arr[2].size() - 2]);
					vertex2.at(2) = stod(splited_arr[2][splited_arr[2].size() - 1]);

					space = getSpace(vertex0, vertex1, vertex2);
					//sum += space;
					array_of_space[round(angle)] += space;
					//std::cout << "SPACEEEEE: " << space << std::endl;
				}
				countOfTriangle += 1;
			}
			str.clear();
		}
		//std::cout << "MIN: " << min << std::endl;
		//std::cout << "MAX: " << max << std::endl;
		//std::cout << "SUM: " << sum << std::endl;

		
		//std::cout << "COUNT OF TRIANGLE: " << countOfTriangle << '\n';
		file.close();

		for (int i = 0; i <= 180; i++)
		{
			if (array_of_space[i] > 0)
			{
				if (maxSpace < array_of_space[i])
					maxSpace = array_of_space[i];
				std::cout << "degre " << (i - 90) << ": " << array_of_space[i] << std::endl;
			}
		}

		if (render(array_of_space, maxSpace) == 1)
		{
			std::cout << "something wrong" << std::endl;
		}
	}
	else
	{
		std::cout << "not arguments" << std::endl;
	}
	return (0);
}