#include "split.hpp"
#include <iostream>

std::vector<std::string>	split(std::string str, std::string delim)
{
    std::vector<std::string>	tokens;
    size_t						pos = 0;
    std::string					token;

    while ((pos = str.find(delim)) != std::string::npos)
	{
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delim.length());
    }
    if (str != "")
        tokens.push_back(str);
    return tokens;
}

std::vector<std::string>	split(std::string str, char delim)
{
    std::vector<std::string>	tokens;
    size_t						pos = 0;
    std::string					token;

    while ((pos = str.find(delim)) != std::string::npos)
	{
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + 1);
    }
    if (str != "")
        tokens.push_back(str);
    return tokens;
}