#include "Webserv.hpp"
#include "../http/server/Server.hpp"
#include "../config/block/ServerBlock.hpp"
#include "../iom/KqueueManage.hpp"

Webserv::Webserv(void) {}
Webserv::Webserv(const Webserv& other) {}
Webserv& Webserv::operator=(const Webserv& other) { return (*this);}
Webserv::~Webserv(void) {}

/*
server & kqueue & client
*/
void Webserv::start(void) {
	std::list<ServerBlock *> sbs;
	Server server("127.0.0.1", 8080, sbs);
	server.init();

	// struct kevent event_list[8]; // kevent array for eventlist

    /* main loop */
    int new_events;
    struct kevent* curr_event;
    while (1)
    {
		usleep(1000000); // delay setting
		KqueueManage::instance().kevent();
        // KqueueManage::instance().changeVec().clear(); // 꼭 해야 하나 고민
		// add 추가
		std::cout << "KqueueManage::instance().eventCount()  : " << KqueueManage::instance().eventCount()  << std::endl;
		// KqueueManage::instance().kqueue();
        for (int i = 0; i < KqueueManage::instance().eventCount() ; ++i)
        {
			std::cout << "i : " << i << " " << KqueueManage::instance().eventCount()  << std::endl;
			//this->_eventArr
			
            curr_event = &KqueueManage::instance().eventArr()[i];
			// std::cout << "curr_event->ident  "  << curr_event->ident  << std::endl;
            if (curr_event->flags & EV_ERROR) {
                if (curr_event->ident == server.getSocket()->getFd())
                    throw IOException("server socket error", errno);
                else
                {
					std::cout << "error !!!!" << std::endl;
					// server.disconnect()
                    // cerr << "client socket error" << endl;
                    // disconnect_client(curr_event->ident, clients);
                }
            }
            else if (curr_event->filter == EVFILT_READ)
            {
                if (curr_event->ident == server.getSocket()->getFd())
                {
                    /* accept new client */
					try {
						Socket* clientSocket = server.connect(server.getSocket());
						std::cout << "new:clientsocket : " <<  clientSocket->getFd() << std::endl;
						clientSocket->setNonBlock();
						KqueueManage::instance().setEvent(clientSocket->getFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
						KqueueManage::instance().setEvent(clientSocket->getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
						// clients[client_socket] = "";
					} catch (IOException e) {}
                }
                else
                {
					std::cout << "read : " << curr_event->ident  << std::endl;
                    /* read data from client */
                    // char buf[1024];
                    // int n = read(curr_event->ident, buf, sizeof(buf));
					bool b = server.clients()[curr_event->ident]->recv(server.clients()[curr_event->ident]->socket());
					// KqueueManage::instance().create(client)
					if (b == false) {
						server.clients().erase(curr_event->ident);
						KqueueManage::instance().delEvent(curr_event->ident);
						// throw IOException("recv error : ", errno);
                        // disconnect_client(curr_event->ident, clients);
					} else {
						std::cout << "connect cnt : " << Client::_s_connCnt << std::endl;
                        // buf[n] = '\0';
                        // clients[curr_event->ident] += buf;
                        // cout << "received data from " << curr_event->ident << ": " << clients[curr_event->ident] << endl;
                    }
                }
            }
            else if (curr_event->filter == EVFILT_WRITE)
            {
                /* send data to client */
				 std::cout << "writefilter: " << curr_event->ident <<  std::endl;
				//  std::cout << server.clients()[curr_event->ident]->socket(). << std::endl;
				// bool b;
				bool b = server.clients()[curr_event->ident]->send(server.clients()[curr_event->ident]->socket());
				std::cout << "asgrawegawefg!???????????" << std::endl;
				if (b == false) {
					std::cout << "write fail " << std::endl;
					//disconnect_client(curr_event->ident, clients);  
				} else {
					// std::cout << "write erase" << std::endl;
					server.clients().erase(curr_event->ident);
				}
            }
        }
    }
}

void Webserv::stop(void) {

}