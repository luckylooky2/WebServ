#include "Request.hpp"
#include <iostream>

Request::Request(std::string __reqString)
: _reqString(__reqString)
{
	_requestLine = _parser.parseRequestLine(_reqString.getRequestLine());
	_headers = _parser.parseHeaders(_reqString.getHeaders());
}

Request::~Request() {}

RequestString	Request::getReqString() { return (_reqString); }
RequestLine		Request::getRequestLine() { return (_requestLine); }
Headers			Request::getHeaders() { return (_headers); }