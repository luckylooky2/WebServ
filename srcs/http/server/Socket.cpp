#include "Socket.hpp"

Socket::Socket(int fd) : FileDescriptor(fd) {}

Socket* Socket::create(void) {
	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		throw IOException("socket create : ", errno);
	return (new Socket(fd));
}

Socket::~Socket() throw() {}

void Socket::bind(void) {
}

void Socket::accept() {}

void Socket::listen() {}

void Socket::recv() {}

void Socket::send() {}