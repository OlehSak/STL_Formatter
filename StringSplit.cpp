#include "StringSplit.h"
#include <stdlib.h>
#include <cstring>

StringSplit::StringSplit(void)
{
}

StringSplit::StringSplit(StringSplit const& src)
{
	*this = src;
}

size_t	StringSplit::get_count(char const* s, char c)
{
	size_t i;

	i = 0;
	while (*s)
	{
		if ((*s) != c)
		{
			i++;
			while (*s != c && *s)
				s++;
		}
		if (*s)
			s++;
	}
	return (i);
}

void	bzero(void* s, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		((char*)s)[i] = '\0';
		i++;
	}
}

void* memalloc(size_t size)
{
	char* mem;

	mem = (char*)malloc(size);
	if (mem)
		bzero(mem, size);
	return (mem);
}

char* ft_strnew(size_t size)
{
	return (char*)memalloc(size + 1);
}

char* StringSplit::get_word(char const** s, char c)
{
	const char* end;
	char* ret_str;

	ret_str = 0;
	while (**s)
	{
		if (**s != c)
		{
			end = strchr(*s, c);
			if (!end)
				return (_strdup(*s));
			ret_str = ft_strnew(end - (*s));
			if (ret_str)
			{
				memmove(ret_str, *s, end - (*s));
				*s = end;
				break;
			}
		}
		(*s)++;
	}
	return (ret_str);
}

char** StringSplit::strsplit(char const* s, char c)
{
	char** ret_arr;
	char* str;
	size_t	word_count;
	size_t	i;

	word_count = 0;
	ret_arr = 0;
	if (s && c >= 0)
	{
		word_count = get_count(s, c);
		ret_arr = (char**)malloc(sizeof(char*) * (word_count + 1));
		if (ret_arr)
		{
			i = -1;
			while (++i < word_count)
			{
				str = get_word(&s, c);
				if (str)
					ret_arr[i] = str;
			}
			ret_arr[i] = 0;
		}
	}
	return (ret_arr);
}

StringSplit::~StringSplit()
{
}