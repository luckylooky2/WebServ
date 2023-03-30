#ifndef HEADERS_HPP
#define HEADERS_HPP
#include <map>
#include <string>
#include <vector>

/**
 * @brief HTTP 요청 메시지 중 헤더를 저장
 * @details 필드 이름 별로 필드 값을 중복하여 저장
 * @author chanhyle
 * @date 2023.03.29
 */
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