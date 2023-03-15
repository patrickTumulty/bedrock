//
// Created by Patrick Tumulty on 5/15/22.
//

#ifndef RHC_STRINGUTILS_H
#define RHC_STRINGUTILS_H

#include <string>
#include <vector>

class StringUtils
{
public:
    static std::string toUpper(const std::string& s);
    static bool endsWith(const std::string& s, const std::string& suffix);
    static bool startsWith(const std::string& s, const std::string& prefix);
    static std::string replace(const std::string& s, const std::string& subString, const std::string& replacement);
    static std::string int2hex(int number);
    static std::vector<std::string> split(const std::string& s, const std::string& delimiter);
    static std::string trimTillFirstL(const std::string& s, const std::string& token);
    static std::string trimTillFirstR(const std::string& s, const std::string& token);
    static void trimL(std::string &s);
    static void trimR(std::string &s);
    static void trim(std::string &s);
};


#endif //RHC_STRINGUTILS_H
