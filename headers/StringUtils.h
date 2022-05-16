//
// Created by Patrick Tumulty on 5/15/22.
//

#ifndef RHC_STRINGUTILS_H
#define RHC_STRINGUTILS_H

#include <string>

class StringUtils
{
public:
    static std::string toUpper(const std::string& s);
    static bool endsWith(const std::string& s, const std::string& suffix);
    static bool startsWith(const std::string& s, const std::string& prefix);
    static std::string replace(const std::string& s, const std::string& subString, const std::string& replacement);
    static std::string int2hex(int number);
};


#endif //RHC_STRINGUTILS_H
