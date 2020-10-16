#include <fstream>
#include <iostream>
#include <string>
#include "CalculateS.h"
#include "StringSplit.h"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		std::cout << argv[1] << std::endl;

		long int countOfTriangle;
		std::size_t found;

		std::string str;
		std::ifstream file(argv[1]);
		StringSplit array;
		char** splited;

		countOfTriangle = 0;
		while(std::getline(file, str))
		{
			std::string key("facet normal");
			std::size_t found = str.rfind(key);
			if (found != std::string::npos)
			{
				splited = array.strsplit(str.c_str(), ' ');
				std::cout << splited[2] << ' ' << splited[3] << ' ' << splited[4] << std::endl;

				countOfTriangle += 1;
			}
			std::cout << str << ' ' << str.length() << std::endl;
			str.clear();
		}
		std::cout << "COUNT OF TRIANGLE: " << countOfTriangle << '\n';
		file.close();
	}
	else
	{
		std::cout << "not arguments" << std::endl;
	}
	return (0);
}