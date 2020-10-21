﻿#include "Header.h"

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

int main(int argc, char** argv)
{
	std::string input;
	bool breaker = true;
	std::ifstream	file(input);

	while (breaker)
	{
		std::cout << "Type *.stl filename or 'close' for close:" << std::endl;
		std::cin >> input;

		std::ifstream	file(input);
		if (input == "close")
			return (0);
		if (file.fail() || !fileChecker(input))
		{
			std::cout << "Wrong file or file not fount." << std::endl;
		}
		else
			break;
	}

	if (input.length() > 0)
	{
		std::ifstream	file(input);

		long int countOfTriangle;

		std::string		str;

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

		std::cout << "Loading..." << std::endl;

		while(std::getline(file, str))
		{
			std::string key("facet normal");
			auto found = str.rfind(key);
			if (found != std::string::npos)
			{
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
					array_of_space[round(angle)] += space;
				}
				countOfTriangle += 1;
			}
			str.clear();
		}
		file.close();

		for (int i = 0; i <= 180; i++)
		{
			if (array_of_space[i] > 0)
			{
				if (maxSpace < array_of_space[i])
					maxSpace = array_of_space[i];
			}
		}

		std::cout << "Vertical axis, maximum space: " << maxSpace << std::endl;
		std::cout << "Horizontal axis: -90; 0; 90 degrees" << std::endl;

		if (render(array_of_space, maxSpace) == 1)
		{
			std::cout << "something wrong" << std::endl;
		}
	}
	else
	{
		return(1);
	}
	return (0);
}