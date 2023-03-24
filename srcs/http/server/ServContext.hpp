
#ifndef SERVCONTEXT_HPP
#define SERVCONTEXT_HPP

#include "Common.hpp"

/*
	deprecated
*/
class ServContext {
private:
	Tokens		tokens;
	//Listens		listens;
	Methods		methods;
	ErrorPages	errorPages;
	
public:
	ServContext(void);
};

#endif