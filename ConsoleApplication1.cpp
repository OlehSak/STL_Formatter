#include <fstream>
#include <iostream>
#include <string>
#include "CalculateS.h"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		std::cout << argv[1] << std::endl;

		long int countOfTriangle;
		std::size_t found;

		std::string str;
		std::ifstream file(argv[1]);

		countOfTriangle = 0;
		while(std::getline(file, str, '\n'))
		{
			found = str.rfind("facet normal");
			if (found)
			{
				countOfTriangle += 1;
			}
			std::cout << str << ' ' << str.length() << ' ' << found << std::endl;
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