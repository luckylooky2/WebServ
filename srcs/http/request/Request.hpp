#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "RequestString.hpp"
#include "RequestParser.hpp"
#include "RequestLine.hpp"
#include "Headers.hpp"

// 1. 요청을 받는다 : HTTP 요청 메시지를 네트워크로부터 읽어 들인다. => RequestMessage class
// 2. 요청을 처리한다 : 요청 메시지를 해석하고 행동을 취한다. => RequestAction class
// 3. 리소스에 접근한다 : 메시지에서 지정한 리소스에 접근한다. => RequestResource class

class Request {

public:
	typedef std::map<std::string, std::vector<std::string> >	headers_map;

public:
	Request();
	~Request();
	Request(const Request& __copy);
	Request	operator=(const Request& __copy);

	Request(std::string __reqString);
	
	RequestString	getReqString();
	RequestLine		getRequestLine();
	Headers			getHeaders();

	e_method		method();
	std::string		uri();
	float			version();
	headers_map		headers();
	std::string		body();
	size_t			headerCount();

private:
	RequestString	_reqString;
	RequestParser	_parser; // 필요한가?
	RequestLine		_requestLine;
	Headers			_headers;
	std::string		_body;
};

#endif