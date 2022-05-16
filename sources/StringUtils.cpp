//
// Created by Patrick Tumulty on 5/15/22.
//

#include "StringUtils.h"
#include <algorithm>
#include <sstream>

/**
 * Convert a string to uppercase
 *
 * @param s input string
 * @return uppercase input string
 */
std::string StringUtils::toUpper(const std::string& s)
{
    std::string str(s);
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

bool StringUtils::startsWith(const std::string &s, const std::string &prefix)
{
    if (prefix.length() > s.length()) return false;
    for (int i = 0; i < prefix.length(); i++)
        if (prefix.at(i) != s.at(i))
            return false;
    return true;
}

bool StringUtils::endsWith(const std::string &s, const std::string &suffix)
{
    if (suffix.length() > s.length()) return false;
    for (int i = 0; i < suffix.length(); i++)
        if (suffix.at((suffix.length() - 1) - i) != s.at((s.length() - 1) - i))
            return false;
    return true;
}

std::string StringUtils::replace(const std::string &s, const std::string &subString, const std::string &replacement)
{
    return std::string(s).replace(s.find(subString, 0), subString.length(), replacement);;
}

std::string StringUtils::int2hex(int number)
{
    std::ostringstream ss;
    ss << std::hex << number;
    return ss.str();
}

