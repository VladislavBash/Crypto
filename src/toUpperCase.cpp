#include "toUpperCase.hpp"
#include <locale>

std::string toUpperCase(std::string str)
{
    std::locale locale("");
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}