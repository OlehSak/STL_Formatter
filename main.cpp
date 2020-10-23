#include "Header.h"
#include "Renderer.h"

bool fileChecker(std::string input)
{
	if (input.length() > 4)
	{
		if (input[input.length() - 1] == 'l' &&
			input[input.length() - 2] == 't' &&
			input[input.length() - 3] == 's' &&
			input[input.length() - 4] == '.')
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

int main(int argc, char** argv)
{
	std::string		input = initialize();

	std::ifstream	file(input);
	if (!file.is_open())
	{
		return(1);
	}

	std::string		str;

	std::vector<std::string>	splited_arr[3];
	std::vector<std::string>	splited;
	double sum;

	double min = 90;
	double max = 0;
	double maxSpace = 0;

	std::vector<double> array_of_space;
	array_of_space.resize(181);

	sum = 0;

	std::cout << "Loading..." << std::endl;

	while (std::getline(file, str))
	{
		std::string key("facet normal");
		auto found = str.rfind(key);
		if (found != std::string::npos)
		{
			std::vector<double> facet;
			facet.resize(3);

			splited = split(str, ' ');

			facet.at(0) = stod(splited[splited.size() - 3]);
			facet.at(1) = stod(splited[splited.size() - 2]);
			facet.at(2) = stod(splited[splited.size() - 1]);

			double angle = angleCalculetion(facet[0], facet[1], facet[2], 0, 0, 1);

			if (round(angle) > max)
				max = round(angle);
			if (round(angle) < min)
				min = round(angle);

			std::getline(file, str);
			std::string key("outer loop");

			found = str.rfind(key);
			if (found != std::string::npos)
			{
				double space;

				std::vector<double> vertex0;
				std::vector<double> vertex1;
				std::vector<double> vertex2;
				vertex0.resize(3);
				vertex1.resize(3);
				vertex2.resize(3);

				std::string		str[3];

				std::getline(file, str[0]);
				splited_arr[0] = split(str[0], ' ');

				vertex0.at(0) = std::stod(splited_arr[0][splited_arr[0].size() - 3]);
				vertex0.at(1) = std::stod(splited_arr[0][splited_arr[0].size() - 2]);
				vertex0.at(2) = std::stod(splited_arr[0][splited_arr[0].size() - 1]);

				std::getline(file, str[1]);
				splited_arr[1] = split(str[1], ' ');

				vertex1.at(0) = std::stod(splited_arr[1][splited_arr[1].size() - 3]);
				vertex1.at(1) = std::stod(splited_arr[1][splited_arr[1].size() - 2]);
				vertex1.at(2) = std::stod(splited_arr[1][splited_arr[1].size() - 1]);

				std::getline(file, str[2]);
				splited_arr[2] = split(str[2], ' ');

				vertex2.at(0) = std::stod(splited_arr[2][splited_arr[2].size() - 3]);
				vertex2.at(1) = std::stod(splited_arr[2][splited_arr[2].size() - 2]);
				vertex2.at(2) = std::stod(splited_arr[2][splited_arr[2].size() - 1]);

				space = getSpace(vertex0, vertex1, vertex2);
				array_of_space[round(angle)] += space;
			}
		}
		str.clear();
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