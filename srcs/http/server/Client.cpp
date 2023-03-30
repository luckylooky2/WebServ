#include "Client.hpp"

int Client::_s_connCnt = 0;


Client::Client(InetAddress inetAddress, Server& server, Socket& socket)
	: _inetAddress(inetAddress), _server(server), _socket(socket), _in(this->_socket), _out(this->_socket) {
	Client::_s_connCnt++;
}

Client::~Client(void) {
	Client::_s_connCnt--;
	// delete &this->_in;
	// delete &this->_out;
	this->_server.disconnect(*this);
	// delete &this->_socket;
}

Socket& Client::socket() const {
	return (this->_socket);
}

// recv 0 == client에서 접속종료
bool Client::recv(FileDescriptor &fd) {
	(void)fd;
	if (this->_in.recv() <= 0) {
		delete this;
		return (false);
	}
	return (true);
}

bool Client::send(FileDescriptor& fd) {
	
	// response 종료 체크
	// m_out size 체크

	(void)fd;
	std::cout<< "send in in ini " << std::endl;
	std::cout << this->_in.size() << std::endl;
	if (this->_in.size() == 0)
		return (false);
		else
		std::cout << "notnull in " << std::endl;
    ssize_t ret = 0;
	// request, response 로직에서 생서한 응답버퍼 _out 를 send해야 함.
    // if ((ret = this->_out.send()) > 0)
    // if ((ret = this->_in.send()) > 0)
		//std::cout << "out ret : " << ret << std::endl;
 		// 시간 체크
	ret = this->_in.send();
	if (ret == -1)
		delete this;
	return (true);
}