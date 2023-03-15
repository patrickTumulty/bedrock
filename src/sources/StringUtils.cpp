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

/**
 * Split a string by a delimiter
 *
 * @param s string
 * @param delimiter split delimiter
 * @return string vector
 */
std::vector<std::string> StringUtils::split(const std::string &s, const std::string &delimiter)
{
    size_t pos = 0;
    std::string str(s);
    std::string token;
    std::vector<std::string> tokenList;

    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        if (!token.empty()) tokenList.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    if (!token.empty()) tokenList.push_back(str);
    if (tokenList.empty()) tokenList.push_back(s);
    return tokenList;
}

/**
 * Trim the left part of the string up to the first found token, removing the token.
 *
 * @param s input string
 * @param token string token
 * @return trimmed string
 */
std::string StringUtils::trimTillFirstL(const std::string &s, const std::string &token)
{
    std::size_t foundIndex = s.find(token);
    if (foundIndex == std::string::npos) return s;
    return s.substr(foundIndex + token.length());
}

/**
 * Trim the right part of the string up to the first found token, removing the token.
 *
 * @param s input string
 * @param token string token
 * @return trimmed string
 */
std::string StringUtils::trimTillFirstR(const std::string &s, const std::string &token)
{
    std::size_t foundIndex = s.find(token);
    if (foundIndex == std::string::npos) return s;
    return s.substr(0, foundIndex);
}

/**
 * Trim left white space (in place)
 *
 * @param s string to trim
 */
void StringUtils::trimL(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
}

/**
 * Trim right white space (in place)
 *
 * @param s string to trim
 */
void StringUtils::trimR(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

/**
 * Trim left and right white space (in place)
 *
 * @param s string to trim
 */
void StringUtils::trim(std::string &s)
{
    trimL(s);
    trimR(s);
}

