#include "RequestMessage.hpp"

RequestMessage::RequestMessage()
: _method(NONE), _uri(""), _version(0), _headers(string_table()), _header_count(0), _body(string_table())
{}

RequestMessage::RequestMessage(e_method __method, std::string __uri, float __version)
: _method(__method), _uri(__uri), _version(__version), _headers(string_table()), _header_count(0), _body(string_table())
{}

RequestMessage::RequestMessage(const RequestMessage& __copy)
{
    *this = __copy;
}

RequestMessage	RequestMessage::operator=(const RequestMessage& __copy)
{
    if (this != &__copy)
    {
        _method = __copy._method;
        // ...
    }
    return (*this);
}

RequestMessage::~RequestMessage()
{}

e_method	getMethod();
void		setMethod();