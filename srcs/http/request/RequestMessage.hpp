#ifndef REQUESTMESSAGE_HPP
#define REQUESTMESSAGE_HPP

#include <string>
#include <map>

typedef enum s_method
{
  NONE = 0,
  GET,
  POST,
  PUT,
  DELETE,
}	e_method;

class RequestMessage {
public:
	typedef typename std::map<std::string, std::string>	string_table;

private:
	RequestMessage();

public:
	RequestMessage(e_method __method, std::string __uri, float __version);
	RequestMessage(const RequestMessage& __copy);
	RequestMessage	operator=(const RequestMessage& __copy);
	~RequestMessage();
	
	e_method		getMethod();
	std::string		getUri();
	float			getVersion();
	void			addHeader();
	void			deleteHeader();
	void			clearHeader();
	unsigned int	getHeaderCount();
	void			addBody();
	void			deleteBody();
	void			clearBody();
	

private:
	e_method		_method;
	std::string		_uri;
	float			_version;
	string_table	_headers;
	unsigned int	_header_count;
	string_table	_body;
};

#endif