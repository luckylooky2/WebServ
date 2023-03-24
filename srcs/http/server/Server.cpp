#include "Server.hpp"

Server::Server( std::string &host, int port, std::list<ServerBlock *> sb) :
		_host(host),
		_port(port),
		_serverBlocks(sb),
		_socket(*Socket::create())
		//_clients(),
{}