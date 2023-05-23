#include "MethodMaker.hpp"
#include "../../../exception/Exception.hpp"
#include "../HTTPState.hpp"
#include "../Response.hpp"
#include "../../request/Request.hpp"
#include "../../server/Client.hpp"
#include "../method/IMethod.hpp"
#include <iostream>
#include <string>

#include "../method/Method.hpp"


MethodMaker::MethodMaker() {}
MethodMaker::~MethodMaker() {}

void MethodMaker::make(Client& client, Request& req, Response& res, ResponseMaker& maker) {
	try {
		IMethod* method = Method::METHOD[client.parser().method()];
		std::cout << "<MethodMaker::make> in do method !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << client.parser().method() <<  std::endl;
	
		if (method) {
			if (method->doMethod(req, res, client))
				return (maker.executeMaker());

			// if (method.hasBody())
			// 	client.parser().maxBodySize(maxBodySizeFor(request.serverBlock(), request.locationBlock()));

			// if (isAcceptable(request.serverBlock(), request.locationBlock(), method))
			// 	return (next());
		}
		res.status(HTTPStatus::STATE[HTTPStatus::METHOD_NOT_ALLOWED]);
		res.end();
	} catch (Exception &exception) {
		// Failed to do method
		res.status(HTTPStatus::STATE[HTTPStatus::INTERNAL_SERVER_ERROR]);
		maker.executeMaker();
	}
}
