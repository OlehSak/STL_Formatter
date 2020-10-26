#include "Header.h"
#include "Renderer.h"
#include "Calculations.h"

bool fileChecker(std::string input)
{
	if (input.length() > 4)
	{
		if (input.at(input.length() - 1) == 'l' &&
			input.at(input.length() - 2) == 't' &&
			input.at(input.length() - 3) == 's' &&
			input.at(input.length() - 4) == '.')
			return (true);
	}
	return false;
}

std::string	initialize()
{
	auto			breaker = true;
	std::string		input;


	while (breaker)
	{
		std::cout << "Type *.stl filename or 'close' for close:" << std::endl;
		std::cin >> input;

		std::ifstream	file(input);
		if (input == "close")
			break;
		if (file.fail() || !fileChecker(input))
		{
			std::cout << "Wrong file or file not fount." << std::endl;
		}
		else
			break;
	}
	return (input);
}

std::vector<double>	getVertex(std::string str)
{
	std::vector<double> vertex;
	vertex.resize(3);

	auto splited = split(str, ' ');

	vertex.at(0) = std::stod(splited.at(splited.size() - 3));
	vertex.at(1) = std::stod(splited.at(splited.size() - 2));
	vertex.at(2) = std::stod(splited.at(splited.size() - 1));
	return (vertex);
}

int main(int argc, char** argv)
{
	std::string		input = initialize();

	std::ifstream	file(input);
	if (!file.is_open())
	{
		return(1);
	}

	std::string		str;
	auto Calc = new Calculations();

	double maxSpace = 0;

	std::vector<double> array_of_space (181);

	std::cout << "Loading..." << std::endl;

	while (std::getline(file, str))
	{
		auto found = str.find("facet normal");
		int		iterator(0);

		if (found != std::string::npos)
		{
			iterator++;
			auto facet = getVertex(str);
			auto angle = Calc->angleCalculetion(facet.at(0), facet.at(1), facet.at(2), 0, 0, -1);

			std::getline(file, str);

			found = str.find("outer loop");

			if (found != std::string::npos)
			{
				iterator++;

				std::getline(file, str);
				auto vertex0 = getVertex(str);
				iterator++;

				std::getline(file, str);
				auto vertex1 = getVertex(str);
				iterator++;

				std::getline(file, str);
				auto vertex2 = getVertex(str);
				iterator++;


				double space = Calc->getSpace(vertex0, vertex1, vertex2);
				array_of_space.at((int)round(angle)) += space;
			}
			iterator++;
		}
		if (iterator != 0 && iterator != 6)
		{
			std::cout << "Error in file" << std::endl;
			return (1);
		}
	}
	file.close();

	for (auto& num : array_of_space)
	{
		if (num > 0)
		{
			if (maxSpace < num)
				maxSpace = num;
		}
	}

	std::cout << "Vertical axis, maximum space: " << maxSpace << std::endl;
	std::cout << "Horizontal axis: -90; 0; 90 degrees" << std::endl;

	auto Display = new Renderer();

	if (Display->render(array_of_space, maxSpace) == 1)
	{
		std::cout << "something wrong" << std::endl;
	}
	return (0);
}