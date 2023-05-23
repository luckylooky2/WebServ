#include "CGI.hpp"
#include "../../exception/Exception.hpp"
#include "CGITask.hpp"
#include "../response/method/Method.hpp"
#include "../response/method/IMethod.hpp"
#include "../response/HTTPStatus.hpp"
#include "../response/make/ResponseMaker.hpp"
#include "../response/HTTPStatus.hpp"
#include "../server/Client.hpp"
#include "../request/Request.hpp"
#include "../response/ResponseByCGI.hpp"
#include "../response/Response.hpp"
#include "../server/Socket.hpp"
#include <sys/types.h>
#include "../../util/Base.hpp"
#include "../SHTTP.hpp"
#include <iostream>
#include <string>

class Parser;
class ResponseByCGI;

CGITask::CGITask(Client& client, CGI& cgi) :
		_client(client), _cgi(cgi),
		_out(*FileDescriptor::create(_cgi.out())),
		wroteBodyUpTo(), _running(true) {
	IMethod* method = Method::METHOD[client.parser().method()];
	std::cout << "CGITask::CGITask(Client& client, CGI& cgi)  : " << _out.getFd() << " " << method->getHasBody() << _cgi.file().path()  << std::endl;
	KqueueManage::instance().create(this->_cgi.in(), *this);
	KqueueManage::instance().create(this->_out, *this);
	if (method->getHasBody()) {
		KqueueManage::instance().setEvent(_cgi.in().getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	}
	else
		this->_cgi.in().close();
	KqueueManage::instance().setEvent(_cgi.out().getFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
}

CGITask::~CGITask(void) {
		std::cout << "CGITask::~CGITask : " << _cgi.in().getFd() << std::endl;
// std::cout << _cgi.file().path() << std::endl;
	this->_cgi.kill();
	KqueueManage::instance().delEvent(_cgi.in().getFd());
	KqueueManage::instance().delEvent(_cgi.out().getFd());
	delete &_out;
	delete &_cgi;
}

bool CGITask::running() {
	return (_running);
}

bool CGITask::send(FileDescriptor& fd) {
	std::cout << "CGITask::send(FileDescriptor& fd) : " << _client.body().c_str() << "|" << std::endl;
	std::cout << wroteBodyUpTo << " " << _client.body().length() << std::endl;

	if (_cgi.in().isClosed())
		return (true);
	if (wroteBodyUpTo == _client.body().length()) {
		_cgi.in().close();	
		KqueueManage::instance().delEvent(_cgi.in().getFd());
		return (true);
	}

	ssize_t wrote = fd.write(_client.body().c_str() + wroteBodyUpTo, _client.body().length() - wroteBodyUpTo);
	std::cout << "wroteBodyUpTo :  " << wrote << std::endl;

	if (wrote <= 0) {
		this->_cgi.in().close();
		KqueueManage::instance().delEvent(_cgi.in().getFd());
		return (true);
	}

	wroteBodyUpTo += wrote;
	std::cout << "wroteBodyUpTo :  " << wroteBodyUpTo << std::endl;
	std::cout << "wroteBodyUpTo :  " << _client.body().length() << std::endl;
	if (wroteBodyUpTo == _client.body().length()) {
		_cgi.in().close();
		KqueueManage::instance().delEvent(_cgi.in().getFd());
		return (true);
	}
	return (false);
}

bool CGITask::recv(FileDescriptor& fd) {
	(void)fd;
	std::cout << "CGITask::recv(FileDescriptor& fd) : " << "|"  << std::endl;

	// char buf[SHTTP::DEFAULT_READSIZE];
	// this->_out.lseek(0, SEEK_SET);
	std::string ret = this->_out.readString();
	this->_out.store(ret);
	if (ret.empty()) {
		_client.response().status(HTTPStatus::STATE[HTTPStatus::INTERNAL_SERVER_ERROR]);
		_client.maker().executeMaker();
		KqueueManage::instance().setEvent(this->_client.socket().getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
		return (true);
	}

	// if (r == 0 && _out.storage().empty()) {
	// 	_client.response().status(HTTPStatus::STATE[HTTPStatus::GATEWAY_TIMEOUT]);
	// 	_client.maker().executeMaker();
	// 	return (true);
	// }

	Parser parser(_client);
	std::cout << "parser !!!!!!!!!!!!!!!!" << std::endl;
    std::cout << parser.state() << std::endl;
    parser.hState(Parser::FIELD);
	if (parser.state() != Parser::HEND) {
		char c;
		// bool isParse = false;
	try {
		std::cout << "start" << std::endl;
		while (this->_out.getC(c)) {
			this->_out.next();
			parser.headerParse(c);
			if (parser.hState() == Parser::HEND) {
				std::cout << "end!!!" << std::endl;
				// isParse = true;

				parser.header().get(Header::STATUS);
				_client.response().status(HTTPStatus::STATE[HTTPStatus::OK]);

				break;
			}
		}

		this->_client.response().header().contentLength(this->_out.storage().size());
		// this->_client.response().header().append(Header::CONTENT_LENGTH, Base::toString(r, 10));
		this->_client.response().body(new ResponseByCGI(this->_client, *this));
		_client.response().status(HTTPStatus::STATE[HTTPStatus::OK]);
		_client.maker().executeMaker();
		// this->cgi().file().remove();

		KqueueManage::instance().setEvent(this->_client.socket().getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
		return (false);
	}
	catch (Exception &exception) {
		this->_client.response().status(HTTPStatus::STATE[HTTPStatus::INTERNAL_SERVER_ERROR]);
		this->_client.maker().executeMaker();

		KqueueManage::instance().setEvent(this->_client.socket().getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
		return (true);
	}
	}

	if (this->_out.isReadCompleted()) {
		KqueueManage::instance().delEvent(_cgi.in().getFd());
		return (true);
	}
	return (false);
}

bool CGITask::isDone() {
	return (this->_out.isReadCompleted());
}

bool CGITask::hasReadHeaders() {
	return (_client.parser().hState() != Parser::HEND);
}

FileDescriptor& CGITask::out() {
	return (this->_out);
}

bool CGITask::timeoutTouch() {
	if (this->_running) {
		this->_running = this->_cgi.running();
		return (true);
	}
	return (false);
}
