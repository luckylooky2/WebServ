#ifndef REQUESTSTRING_HPP
#define REQUESTSTRING_HPP

#include <string>
#include "../../util/split.hpp"
#include "../../exception/IllegalStateException.hpp"

#define SP		' '
#define CRLF	"\r\n"

/**
 * @brief JSON 형식의 request 메시지를 부분별로 저장
 * @details request 메시지의 시작줄, 헤더, 본문을 각각 string으로 저장
 * @author chanhyle
 * @date 2023.03.24
 */
class RequestString {
private:
	size_t	getRequestLineString(std::string __reqString);
	size_t	getHeadersString(std::string __reqString, size_t __requestLineIndex);
	size_t	getBodyString(std::string __reqString, size_t __headersIndex);

public:
	RequestString();
	RequestString(const RequestString& __copy);
	RequestString	operator=(const RequestString& __copy);
	~RequestString();
	
	RequestString(std::string __reqString);

	std::string		getOrigString();
	std::string		getRequestLine();
	std::string		getHeaders();
	std::string		getBody();

private:
	std::string		_originString;
	std::string		_requestLine;
	std::string		_headers;
	std::string		_body;
};

// 정해진 규칙에 따라 string으로만 자르기
// 여기서 1차 오류 검증 => 어떤 부분까지 검증할 것인지 정할 것

#endif