#include "ResponseByCGI.hpp"
#include "../../file/FileDescriptor.hpp"
#include "../encode/ChunkEncoder.hpp"
#include "../cgi/CGITask.hpp"
#include "../server/Client.hpp"
#include "method/Method.hpp"
#include "../../util/Base.hpp"

ResponseByCGI::ResponseByCGI(Client& client, CGITask& task) : _client(client), _task(task), _isEnd(false) {
	std::cout << "ResponseByCGI::ResponseByCGI : " <<std::endl;
}

ResponseByCGI::~ResponseByCGI(void) {}

bool ResponseByCGI::isSelfManaged() const {
	return (true);
}

bool ResponseByCGI::store(Storage& buffer) {
	// if (this->_task.hasReadHeaders())
	// 	return (false);	

	bool hasResponseBody = this->_client.parser().method().compare("HEAD") != 0;


	// std::cout <<"hasResponseBody : " << this->_task.out().storage() << std::endl;
	if (hasResponseBody) {
		// std::cout << this->_task.out().storage() << std::endl;		
		std::cout << "ChunkEncoder::staticEncode(this->_task.out().storage() : " << ChunkEncoder::staticEncode(this->_task.out().storage()) << "|" << std::endl;
		// buffer.store(ChunkEncoder::staticEncode(this->_task.out().storage()));
		buffer.store(this->_task.out().storage());
		// buffer.store(this->_task.out().storage());
	}

	// if (this->_task.isDone()) {
		// if (hasResponseBody)
			// buffer.store(ChunkEncoder::ZERO);
		this->_isEnd = true;
		return (true);
	// }
	return (false);
}

bool ResponseByCGI::isEnd(void) {
	return (this->_isEnd);
}