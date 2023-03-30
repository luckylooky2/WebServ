#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../../address/InetAddress.hpp"
#include "../../file/FileDescriptor.hpp"
#include "Socket.hpp"
#include "Server.hpp"
// #include "../request/Request.hpp"
// #include "../response/Response.hpp"
#include "RWCallback.hpp"
#include "SocketStorage.hpp"

class Server;
/**
 * @brief 클라이언트 관리
 * @details connection
 * @author seongtki
 * @date 2023.03.26
 */
class Client : public RWCallback {
public:
	static int _s_connCnt;
private:
	InetAddress		_inetAddress;
	Server&			_server;
	Socket&			_socket;
	std::string 	_body;
	SocketStorage 	_in;
	SocketStorage 	_out;
	//State m_state;
	//unsigned long _lastDoTime;
	//RequestParser _parser;
	//Request _request;
	// Response _response;
	bool _keepAlive;

	Client& operator=(const Client& other);
	Client(void);
	Client(const Client& other); // myMap.insert(std::make_pair("moon", 2)); 에서 필요함
public:
	~Client(void);
	Client(InetAddress inetAddress, Server& server, Socket& socket);
	Socket& socket() const;
	bool recv(FileDescriptor& fd);
	bool send(FileDescriptor& fd);
};

#endif