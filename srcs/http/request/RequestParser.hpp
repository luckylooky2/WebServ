#ifndef REQUESTPARSER_HPP
#define REQUESTPARSER_HPP
#include <string>
#include <cstdlib>
#include "RequestLine.hpp"
#include "Headers.hpp"
#include "../../util/split.hpp"
#include "../../util/trim.hpp"
#include "../../exception/IllegalStateException.hpp"

#define SP		' '
#define CRLF	"\r\n"

class RequestParser {
public:
	RequestParser();
	RequestParser(const RequestParser& __copy);
	RequestParser	operator=(const RequestParser& __copy);
	~RequestParser();
	RequestLine	parseRequestLine(std::string __requestLineString);
	Headers		parseHeaders(std::string __headersString);

};

#endif