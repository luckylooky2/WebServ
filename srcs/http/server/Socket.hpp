#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "../../file/FileDescriptor.hpp"
#include "Listen.hpp"

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

class Socket : public FileDescriptor {
private:
	int _server_fd;
	Socket(void);
	Socket(const Socket& other);
	Socket& operator=(const Socket& other);
public:
	Socket(int fd);
	virtual ~Socket() throw();
	Socket* create(void);
	void bind(void);
	void accept();
	void listen();
	void recv();
	void send();
};

#endif