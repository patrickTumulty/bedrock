//
// Created by Patrick Tumulty on 3/27/23.
//

#include <gtest/gtest.h>
#include "PropertiesManager.h"
#include <future>
#include "FileUtils.h"
#include <toml++/toml.h>


TEST(PropertyManagerTests, MultithreadedIdenticalPointersTest)
{
    com::PropertiesManager *pointers[10];

    for (auto & pointer : pointers)
    {
        auto future = std::async([](){ return com::PropertiesManager::getInstance().get(); });
        pointer = future.get();
    }

    auto pm1 = com::PropertiesManager::getInstance();

    for (auto ptr : pointers)
    {
        ASSERT_EQ(pm1.get(), ptr);
    }
}

TEST(PropertyManagerTests, CreateTomlFileTest)
{
    if (std::filesystem::exists("test.toml"))
    {
        std::filesystem::remove("test.toml");
    }

    auto propertiesManager = com::PropertiesManager::getInstance();
    propertiesManager->reInit();

    int num1 = propertiesManager->getPropOrDefault<int>("test", "group1", "number1", 3);
    ASSERT_TRUE(num1 == 3);

    int num2 = propertiesManager->getPropOrDefault<int>("test", "group1", "number1", 50);
    ASSERT_TRUE(num2 == 3);

    propertiesManager->refreshValues();
    ASSERT_TRUE(std::filesystem::exists("test.toml"));

    std::filesystem::remove("test.toml");
}

TEST(PropertyManagerTests, ReadTomlFileTest)
{
    std::string someToml = R"(
        [group1]
        gravity = 20.0
        jump = 5

        [group2]
        java = 17
        compiler = "clang"
        debug = true
    )";

    FileUtils::writeStringToFile("test.toml", someToml);

    auto pm = com::PropertiesManager::getInstance();
    pm->reInit();

    ASSERT_DOUBLE_EQ(pm->getPropOrDefault("test", "group1", "gravity", 9.81), 20.0);
    ASSERT_EQ(pm->getPropOrDefault("test", "group1", "jump", 5), 5);

    ASSERT_EQ(pm->getPropOrDefault("test", "group2", "java", 14), 17);
    ASSERT_EQ(std::string(pm->getPropOrDefault("test", "group2", "compiler", "gcc")), "clang");
    ASSERT_TRUE(pm->getPropOrDefault("test", "group2", "debug", false));

    std::filesystem::remove("test.toml");
}






