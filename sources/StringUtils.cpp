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

/**
 * Check if string starts with prefix
 *
 * @param s string
 * @param prefix prefix string
 * @return true if s starts with prefix
 */
bool StringUtils::startsWith(const std::string &s, const std::string &prefix)
{
    if (prefix.length() > s.length()) return false;
    for (int i = 0; i < prefix.length(); i++)
        if (prefix.at(i) != s.at(i))
            return false;
    return true;
}

/**
 * Check if string ends with suffix
 *
 * @param s string
 * @param suffix suffix string
 * @return true if s ends with suffic
 */
bool StringUtils::endsWith(const std::string &s, const std::string &suffix)
{
    if (suffix.length() > s.length()) return false;
    for (int i = 0; i < suffix.length(); i++)
        if (suffix.at((suffix.length() - 1) - i) != s.at((s.length() - 1) - i))
            return false;
    return true;
}

/**
 * Replace substring with replacement for given string s
 *
 * @param s string
 * @param subString substring
 * @param replacement substring replacement
 * @return string with replacement
 */
std::string StringUtils::replace(const std::string &s, const std::string &subString, const std::string &replacement)
{
    return std::string(s).replace(s.find(subString, 0), subString.length(), replacement);;
}

/**
 * Int to hex conversion
 *
 * @param number integer
 * @return hex string
 */
std::string StringUtils::int2hex(int number)
{
    std::ostringstream ss;
    ss << std::hex << number;
    return ss.str();
}

