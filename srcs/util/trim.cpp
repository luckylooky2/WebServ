#include "trim.hpp"

void	trim(std::string& str)
{
    // Trim leading spaces
    std::string::iterator it = str.begin();
    while (it != str.end() && std::isspace(*it)) {
        ++it;
    }
    str.erase(str.begin(), it);

    // Trim trailing spaces
    it = str.end();
    while (it != str.begin() && std::isspace(*(it - 1))) {
        --it;
    }
    str.erase(it, str.end());
}