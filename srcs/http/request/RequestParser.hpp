#ifndef REQUESTPARSER_HPP
#define REQUESTPARSER_HPP
#include <string>
#include <cstdlib>
#include "RequestLine.hpp"
#include "Headers.hpp"
#include "../parse/Parser.hpp"
#include "../../exception/IllegalStateException.hpp"

class RequestParser : public Parser {
public:
	static RequestLine	parseRequestLine(std::string __requestLineString);
	static Headers		parseHeaders(std::string __headersString);
};

#endif