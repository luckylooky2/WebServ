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
	bool	keyExist(std::string __key);
	void	insertHeader(std::string __fieldName, std::vector<std::string> __values);
	void	addFieldValue(std::string __fieldName, std::vector<std::string> __values);

public:
	header_table	_headers;
	size_t			_header_count;
};

#endif