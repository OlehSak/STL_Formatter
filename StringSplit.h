#include <fstream>
#include <iostream>
#include <string>

class StringSplit
{
protected:
	char*			get_word(char const** s, char c);
	size_t			get_count(char const* s, char c);
public:
	std::string*	strsplit(char const* s, char c);
};