
#include "../../config/block/LocationBlock.hpp"
#include "HTTPFindLocation.hpp"
#include "HTTPLocationInterpretor.hpp"
#include <cstddef>
#include <iostream>
#include <list>
#include <string>

HTTPFindLocation::HTTPFindLocation() :
		_clientPath(""),
		_serverLocations(),
		_locationBlock() {}

HTTPFindLocation::HTTPFindLocation(std::string clientPath, std::list<LocationBlock*> serverLocations) :
		_clientPath(clientPath), _serverLocations(serverLocations), _locationBlock() {}

HTTPFindLocation::HTTPFindLocation(const HTTPFindLocation& other) :
		_clientPath(other._clientPath),
		_serverLocations(other._serverLocations),
		_locationBlock(other._locationBlock) {}

HTTPFindLocation::~HTTPFindLocation(void) {}

HTTPFindLocation& HTTPFindLocation::operator =(const HTTPFindLocation& other) {
	if (this != &other) {
		_clientPath = other._clientPath;
		_serverLocations = other._serverLocations;
		_locationBlock = other._locationBlock;
	}
	return (*this);
}

HTTPFindLocation& HTTPFindLocation::location(const LocationBlock *locationBlock) {
	_locationBlock = locationBlock;
	return (*this);
}

const LocationBlock* HTTPFindLocation::location(void) const {
	return (_locationBlock);
}

HTTPFindLocation& HTTPFindLocation::parse(void) {
	std::list<LocationBlock*>::iterator it = _serverLocations.begin();
	std::list<LocationBlock*>::iterator ite = _serverLocations.end();

	int start;

	std::size_t pos;
	std::size_t new_pos;
	int not_found_middle;
	bool exactEnd = false;

	std::list<HTTPLocationInterpretor> possibleLocationList;
	std::list<HTTPLocationInterpretor> exactEndList;
	
	while (it != ite) {
		HTTPLocationInterpretor interpretor((*it)->getPath(), *it);

		char c;
		start = 0;
		pos = 0;
		new_pos = 0;
		not_found_middle = 0;

		while (interpretor.next(c))
			interpretor.parse(c);

		if (!(interpretor.middleElement().empty())) {
			interpretor.middleList(interpretor.middleElement());
		}
		
		if (!(interpretor.exact().empty()))
		{
			if (interpretor.exact().compare(_clientPath) == 0 || interpretor.exact().compare(_clientPath + "/") == 0)
				possibleLocationList.push_back(interpretor);

				it++;
				continue;
		}
	
		if (interpretor.firstChar() == '/') {
	
			if (!(interpretor.start().empty())) {
				if (_clientPath.compare(0, interpretor.start().size(), interpretor.start()) == 0 || (_clientPath + "/").compare(0, interpretor.start().size(), interpretor.start()) == 0) {
					start = 1;
					pos = interpretor.start().size();
				}
				else {
					it++;
					continue;
				}
			}
		}
		else {
			exactEnd = true;
		}
				
		if (start) {
			if (exactEnd) {
				exactEndList.push_back(interpretor);
			} else
				possibleLocationList.push_back(interpretor);
		}
		it++;
	}
	std::list<HTTPLocationInterpretor> &listToCheck = possibleLocationList;
	if (!exactEndList.empty())
	{
		listToCheck.clear();
		listToCheck = exactEndList;
	}

	location(listToCheck.begin()->locationBlock());
	
	return (*this);
}
