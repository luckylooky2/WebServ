#include "Request.hpp"

/* 
	OCCF
*/

Request::Request() {}

Request::Request(const Request& __copy)
{
	_reqString = __copy._reqString;
	_parser = __copy._parser;
	_requestLine = __copy._requestLine;
	_headers = __copy._headers;
	_body = __copy._body;
}

Request	Request::operator=(const Request& __copy)
{
	if (this != &__copy)
	{
		_reqString = __copy._reqString;
		_parser = __copy._parser;
		_requestLine = __copy._requestLine;
		_headers = __copy._headers;
		_body = __copy._body;
	}
	return (*this);
}

Request::~Request() {}

/*
	Member functions
*/

Request::Request(std::string __reqString)
: _reqString(__reqString)
{
	_requestLine = _parser.parseRequestLine(_reqString.getRequestLine());
	_headers = _parser.parseHeaders(_reqString.getHeaders());
	_body = _reqString.getBody();
}
RequestString	Request::getReqString() { return (_reqString); }
RequestLine		Request::getRequestLine() { return (_requestLine); }
Headers			Request::getHeaders() { return (_headers); }

e_method		Request::method() { return (_requestLine._method); }
std::string		Request::uri() { return (_requestLine._uri); }
float			Request::version() { return (_requestLine._version); }
std::map<std::string, std::vector<std::string> >		Request::headers() { return (_headers._headers); }
std::string		Request::body() { return (_body); }
size_t			Request::headerCount() { return (_headers._header_count); }