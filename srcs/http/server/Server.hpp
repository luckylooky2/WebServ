#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include "ServContext.hpp"
#include "Common.hpp"
#include "Socket.hpp"
#include "../../config/block/ServerBlock.hpp"
#include <list>
class Server {
private:
	Socket&					_socket;
	std::string				_host;
	int							_port;
	std::list<ServerBlock>&		_serverBlocks;
	//std::clist<Client>		_clients;
	
	//int			_maxFd;
	//int			_readFd;
	//int			_writeFd;
	ServContext	_servContext;
	Server(void);
public:
	Server( std::string host, int port,  std::list<ServerBlock *> sb);
};

#endif