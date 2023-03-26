#ifndef REQUESTLINE_HPP
#define REQUESTLINE_HPP
#include <string>

typedef enum s_method
{
  NONE = 0,
  GET,
  POST,
  PUT,
  DELETE,
}	e_method;

struct RequestLine {
	e_method		  _method;
	std::string		_uri;
	float			  _version;
};

#endif