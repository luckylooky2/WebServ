#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <string>

#define SP		' '
#define CRLF	"\r\n"

class Parser {
public :
	static std::vector<std::string>		split(std::string str, std::string delim);
	static std::vector<std::string>		split(std::string str, char delim);
	static void							trim(std::string& str);
};

#endif