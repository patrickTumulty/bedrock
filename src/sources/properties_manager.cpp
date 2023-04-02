//
// Created by Patrick Tumulty on 3/26/23.
//

#include "properties_manager.h"
#include <filesystem>
#include "string_utils.h"
#include "file_utils.h"
#include <vector>

using namespace bedrock;

#define PROPERTIES_DOT_TOML "properties.toml"
#define TOML_EXT ".toml"
#define PROPERTY_FILE_GROUP "property_paths"
#define PROPERTY_FILE_KEY "paths"

PropertiesManager::PropertiesManager()
{
    initPropertyManager();
}

void PropertiesManager::initPropertyManager()
{
    auto path = std::filesystem::current_path();
    std::vector<std::string> directoryPaths;

    addDirectoryPaths(path, &directoryPaths);

    directoryPaths.push_back(path.string());

    for (const std::string& dirPath : directoryPaths)
    {
        iterateDirectoriesForTomlFiles(dirPath);
    }
}

void PropertiesManager::addDirectoryPaths(const std::filesystem::path &path, std::vector<std::string> *directoryPaths)
{
    for (const auto& p : std::filesystem::directory_iterator(path))
    {
        std::string filename = p.path().filename();
        if (filename == PROPERTIES_DOT_TOML)
        {
            auto result = toml::parse_file(p.path().string());
            if (!result.empty())
            {
                toml::array& arr = *result[PROPERTY_FILE_GROUP][PROPERTY_FILE_KEY].as_array();
                for (auto&& elem : arr)
                {
                    elem.visit([directoryPaths](auto&& el) noexcept
                               {
                                   if constexpr (toml::is_string<decltype(el)>)
                                       directoryPaths->push_back(std::string(el));
                               });
                }
            }
        }
    }
}

void PropertiesManager::iterateDirectoriesForTomlFiles(const std::filesystem::path &path)
{
    for (const auto& p : std::filesystem::directory_iterator(path))
    {
        std::string pathString = p.path().string();
        if (StringUtils::endsWith(pathString, TOML_EXT))
        {
            std::string categoryName = StringUtils::replace(p.path().filename(), ".toml", "");
            categoriesMap.emplace(categoryName, std::make_shared<PropertiesCategory>(pathString));
        }
    }
}

PropertiesManager::~PropertiesManager()
{
    categoriesMap.clear();
}

std::shared_ptr<PropertiesManager> PropertiesManager::getInstance()
{
    std::scoped_lock lock { PropertiesManager::instanceLock };

    if (instance == nullptr)
    {
        struct concrete : public PropertiesManager {};
        PropertiesManager::instance = std::make_shared<concrete>();
    }

    return PropertiesManager::instance;
}

void PropertiesManager::createNewPropertiesCategory(const std::string &category)
{
    std::string fullPath = StringUtils::format("%s%c%s.toml",
                                           std::filesystem::current_path().string().c_str(),
                                           std::filesystem::path::preferred_separator,
                                           category.c_str());
    categoriesMap.emplace(std::string(category), std::make_shared<PropertiesCategory>(fullPath));
}

void PropertiesManager::refreshValues()
{
    for (auto& iter : categoriesMap)
    {
        iter.second->refreshValues();
    }
}

void PropertiesManager::reInit()
{
    categoriesMap.clear();

    initPropertyManager();
}

PropertiesManager::PropertiesCategory::PropertiesCategory(const std::string& path) : path(path), fileParser()
{
    fileUpdateRequired = false;

    if (!std::filesystem::exists(path))
    {
        FileUtils::writeStringToFile(path, "");
    }
    fileParser = toml::parse_file(path);
}

void PropertiesManager::PropertiesCategory::updateFileIfRequired()
{
    std::scoped_lock lock { fileLock };

    if (!fileUpdateRequired)
        return;

    std::stringstream ss;
    ss << fileParser;
    FileUtils::writeStringToFile(path, ss.str());

    fileUpdateRequired = false;
}

void PropertiesManager::PropertiesCategory::refreshValues()
{
    updateFileIfRequired();

    fileParser.clear();
    fileParser = toml::parse_file(path);
}

PropertiesManager::PropertiesCategory::~PropertiesCategory()
{
    updateFileIfRequired();
}

