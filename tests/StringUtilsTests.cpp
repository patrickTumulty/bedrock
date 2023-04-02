//
// Created by Patrick Tumulty on 4/1/23.
//

#include <gtest/gtest.h>
#include "StringUtils.h"


TEST(StringUtilsTests, FormatTest)
{
    std::string hello = "Hello";
    char ch = ',';
    uint8_t num = 15;

    std::string fmt = com::StringUtils::format("%s%c World!: %d 0x%X %%", hello.c_str(), ch, num, num);

    ASSERT_EQ("Hello, World!: 15 0xF %", fmt);
}