#include "Webserv.hpp"
#include "../config/block/ServerBlock.hpp"
#include "../config/Config.hpp"
#include "../iom/KqueueManage.hpp"
#include "../http/server/Server.hpp"
#include "../log/LogFactory.hpp"
#include "../util/Base.hpp"
#include "SHTTP.hpp"

Logger& Webserv::logger = LogFactory::get("Webserv");

Webserv::Webserv(void) {}
Webserv::Webserv(const ServerList& server) : _servers(server), _isRun(false), _isStop(false) {}

Webserv::Webserv(const Webserv& other) {
	(void)other;
}

Webserv& Webserv::operator=(const Webserv& other) {
	(void)other;
	return (*this);
}

Webserv::~Webserv(void) {}

Server& Webserv::getServer(unsigned long ident) {
	int serverFd = KqueueManage::instance().serverFd((int)ident);
	for (std::list<Server*>::iterator it = this->_servers.begin(); it != this->_servers.end(); it++) {
		if ((*it)->getSocket()->getFd() == serverFd) {
			return *(*it);
		}
	}
	return (*this->_servers.front());
}

void Webserv::run(void) {

	std::cout << "this->_servers.size() : " << this->_servers.size() << std::endl;

	for (std::list<Server*>::iterator it = _servers.begin(); it != _servers.end(); it++)
		(*it)->init();
	this->_isRun = true;

    struct kevent* curr_event;
    while (this->_isRun) {
		KqueueManage::instance().kevent();
		// std::cout << "KqueueManage::instance()._changeVec.size()" << KqueueManage::instance()._changeVec.size() << std::endl;
		(&KqueueManage::instance())->_changeVec.clear();
		std::cout << "kevent : " << KqueueManage::instance().eventCount() <<  std::endl;
        for (int i = 0; i < KqueueManage::instance().eventCount() ; ++i) {
            curr_event = &KqueueManage::instance().eventArr()[i];
			Server& server = getServer(curr_event->ident);
			//  (&KqueueManage::instance())->changeVec().clear();
			std::cout << "curr_event->ident : " << curr_event->ident <<  " " << KqueueManage::instance().eventCount() <<  std::endl;
			
            if (curr_event->flags & EV_ERROR) {
                if (curr_event->ident == (unsigned long)server.getSocket()->getFd())
                    throw IOException("server socket error", errno);
                else
                {
					std::cerr << "error !!!!" << std::endl;
					// server.disconnect()
                }
            }
            else if (curr_event->filter == EVFILT_READ)
            {
                if (curr_event->ident == (unsigned long)server.getSocket()->getFd())
                {
                    /* accept new client */
					try {
						Socket* clientSocket = server.connect(server.getSocket());
						std::cout << "new:clientsocket : " <<  clientSocket->getFd() << " " << curr_event->ident << std::endl;
						KqueueManage::instance().setEvent(clientSocket->getFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
						// KqueueManage::instance().setEvent(clientSocket->getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
					} catch (IOException e) {}
                }
                else
                {
					std::cout << "webserv:read : " << curr_event->ident  << std::endl;
                    /* read data from client */
					bool b = KqueueManage::instance().recv(curr_event->ident);
					if (b == false) {
						//std::cout <<"read false =================================================================";
						server.clients().erase(curr_event->ident);
						KqueueManage::instance().delEvent(curr_event->ident);
						// throw IOException("recv error : ", errno);
					} else {
						// std::cout << "connect cnt : " << Client::_s_connCnt << std::endl;
                    }
                }
            }
            else if (curr_event->filter == EVFILT_WRITE)
            {
				std::cout << "writefilter: " << curr_event->ident <<  std::endl;
				if (server.clients()[curr_event->ident]) {
					// std::cout << "server.clients()[curr_event->ident]->state() : " << server.clients()[curr_event->ident]->response().state() << std::endl;
					// if (server.clients()[curr_event->ident]->state() != server.clients()[curr_event->ident]->END) {
					if (server.clients()[curr_event->ident]->response().isEnd() != true) {
					// if (!server.clients()[curr_event->ident]->in().storage().empty()) {
						// server.clients().erase(curr_event->ident);
						// KqueueManage::instance().delEvent(curr_event->ident);
						std::cout << "not end " << curr_event->ident << std::endl;
						continue;
					}
					bool b = KqueueManage::instance().send(curr_event->ident);
					if (b == false) {
						std::cout << "write fail " << std::endl;
						server.clients().erase(curr_event->ident);
						delete server.clients()[curr_event->ident];
						KqueueManage::instance().delEvent(curr_event->ident);
					} else {
						std::cout << "write treutrue" << std::endl;
						server.clients().erase(curr_event->ident);
						delete server.clients()[curr_event->ident];
						KqueueManage::instance().delEvent(curr_event->ident);
					}
				} else {
					KqueueManage::instance().send(curr_event->ident);
					//KqueueManage::instance().delEvent(curr_event->ident);
				}
            } else {
			} 
		}
		// std::cout << "KqueueManage::instance()._changeVec.size() ebd?? " << KqueueManage::instance()._changeVec.size() << std::endl;
		for (std::list<Server*>::iterator it = _servers.begin(); it != _servers.end(); it++)
			(*it)->checkTimeout();
		if (this->_isStop == true) {
			if (KqueueManage::instance().eventCount() < 1) {
				this->_isRun = false;
				break;
			}
		}
    }


	while (!_servers.empty()) {
		ServerList::iterator it = _servers.begin();
		Server &server = *(*it);

		try {
			KqueueManage::instance().delEvent(server.getSocket()->getFd());
			server.close();
		}
		catch (Exception& exception) {
			// logger.error("Failed to terminate: " + server.getHost() + ":" + Base::toString(server.getPort(),10) + ": " + exception.message());
		}
		delete &server;
		_servers.erase(it);
	}
}

Webserv* Webserv::create(void) {

	typedef std::map<int, std::list<ServerBlock*> > port_map;
	typedef port_map::const_iterator port_iterator;

	typedef std::map<std::string, port_map> host_map;
	typedef host_map::const_iterator host_iterator;

	host_map hostToPortToServersMap;

	RootBlock* rootBlock = Config::instance().rootBlock();
	
	std::list<ServerBlock*> serverBlocks = rootBlock->ServerBlockList();
	for (std::list<ServerBlock*>::iterator sit = serverBlocks.begin(); sit != serverBlocks.end(); sit++) {
		ServerBlock &serverBlock = *(*sit);
		
		std::string host = (serverBlock.getServerName().empty() == false) ? serverBlock.getServerName() : SHTTP::DEFAULT_HOST;
		int port = (serverBlock.getListen() != 0) ? serverBlock.getListen() : SHTTP::DEFAULT_PORT;
		hostToPortToServersMap[host][port].push_back(&serverBlock);
	}

	ServerList httpServers;
	for (host_iterator hit = hostToPortToServersMap.begin(); hit != hostToPortToServersMap.end(); hit++)
	{
		const std::string &host = hit->first;
		const port_map &portMap = hit->second;

		for (port_iterator pit = portMap.begin(); pit != portMap.end(); pit++)
		{
			short port = pit->first;
			std::list<ServerBlock*> serverBlocks = pit->second;

			httpServers.push_back(new Server(host, port, serverBlocks));
		}
	}
	return (new Webserv(httpServers));
}

void Webserv::stop(void) {
	for (ServerList::iterator it = _servers.begin(); it != _servers.end(); it++)
		KqueueManage::instance().delEvent((*it)->getSocket()->getFd());
	this->_isStop = true;
}