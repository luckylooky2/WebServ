#include "Headers.hpp"
#include <iostream>

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

void	Headers::insertHeader(std::string __fieldName, std::vector<std::string> __values)
{
	_headers.insert(std::make_pair(__fieldName, std::vector<std::string>()));
	for (size_t i = 0; i < __values.size(); i++)
		_headers[__fieldName].push_back(__values[i]);
	_header_count++;
}

void	Headers::addFieldValue(std::string __fieldName, std::vector<std::string> __values)
{
	for (size_t i = 0; i < __values.size(); i++)
		_headers[__fieldName].push_back(__values[i]);
}

Headers::Headers()
: _headers(header_table()), _header_count(0)
{

}