class StringSplit
{
protected:
	char*			get_word(char const** s, char c);
	size_t			get_count(char const* s, char c);
public:
	StringSplit();
	~StringSplit();
	StringSplit(StringSplit const& src);

	char**	strsplit(char const* s, char c);
};