//
// Created by Patrick Tumulty on 5/15/22.
//

#ifndef RHC_STRINGUTILS_H
#define RHC_STRINGUTILS_H

#include <string>
#include <vector>
#include "bedrock.h"

BEDROCK_NAMESPACE_START

namespace StringUtils
{
    template<typename ... Args>
    std::string format(const std::string& format, Args ... args)
    {
        int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
        auto size = static_cast<size_t>(size_s);
        std::unique_ptr<char[]> buf(new char[size]);
        std::snprintf(buf.get(), size, format.c_str(), args ...);
        return { buf.get(), buf.get() + size - 1 };
    }

    std::string toUpper(const std::string& s);
    bool endsWith(const std::string& s, const std::string& suffix);
    bool startsWith(const std::string& s, const std::string& prefix);
    std::string replace(const std::string& s, const std::string& subString, const std::string& replacement);
    std::string int2hex(int number);
    std::vector<std::string> split(const std::string& s, const std::string& delimiter);
    std::string trimTillFirstL(const std::string& s, const std::string& token);
    std::string trimTillFirstR(const std::string& s, const std::string& token);
    void trimL(std::string &s);
    void trimR(std::string &s);
    void trim(std::string &s);
};

BEDROCK_NAMESPACE_END

#endif //RHC_STRINGUTILS_H
