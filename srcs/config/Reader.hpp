#ifndef READER_HPP
#define READER_HPP

#include <string>

#define ISSPACE		"\t\n\v\f\r "
#define SEMICOLON	";"

class Reader {
private:
	std::string _parser;
	Reader(const Reader& other);
	Reader& operator=(const Reader &other);
public:
	Reader(void);
	Reader(const std::string& source);
	virtual ~Reader(void);

public:
	std::string
	read(void);

public:
	static Reader from(const std::string& path);
};

#endif
