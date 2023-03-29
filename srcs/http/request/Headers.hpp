#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <map>
#include <string>
#include <vector>

struct Headers {
public:
	typedef std::map<std::string, std::vector<std::string> >	header_table;

public:
	Headers();
	~Headers();
	Headers(const Headers& __copy);
	Headers	operator=(const Headers& __copy);
	
	bool	keyExist(std::string __key);
	void	insertHeader(std::string __fieldName, std::string __fieldValue);
	void	addFieldValue(std::string __fieldName, std::string __fieldValue);

public:
	header_table	_headers;
	size_t			_header_count;
};

#endif