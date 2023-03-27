#include "Headers.hpp"

/*
	OCCF
*/

Headers::Headers() : _headers(header_table()), _header_count(0) {}

Headers::Headers(const Headers& __copy)
{
	_headers = __copy._headers;
	_header_count = __copy._header_count;
}

Headers	Headers::operator=(const Headers& __copy)
{
	if (this != &__copy)
	{
		_headers = __copy._headers;
		_header_count = __copy._header_count;
	}
	return (*this);
}

Headers::~Headers() {}

/*
	Member functions
*/

bool	Headers::keyExist(std::string __key)
{
	header_table::iterator	it = _headers.begin();
	header_table::iterator	ite = _headers.end();

	while (it != ite)
	{
		if (it->first == __key)
			return true;
		it++;
	}
	return false;
}

void	Headers::insertHeader(std::string __fieldName, std::string __fieldValue)
{
	_headers.insert(std::make_pair(__fieldName, std::vector<std::string>()));
	_headers[__fieldName].push_back(__fieldValue);
	_header_count++;
}

void	Headers::addFieldValue(std::string __fieldName, std::string __fieldValue)
{
	_headers[__fieldName].push_back(__fieldValue);
}
