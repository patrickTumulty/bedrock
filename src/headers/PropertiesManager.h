//
// Created by Patrick Tumulty on 3/26/23.
//

#ifndef SLACK_JAW_PROPERTIESMANAGER_H
#define SLACK_JAW_PROPERTIESMANAGER_H

#include <memory>
#include <mutex>
#include "CommonPPAPI.h"
#include "StringUtils.h"
#include <toml++/toml.h>
#include <map>

COMMON_PP_NAMESPACE_START

class PropertiesManager
{
    friend PropertiesManager;
    class PropertiesCategory;
public:
    static std::shared_ptr<PropertiesManager> getInstance();
    PropertiesManager(const PropertiesManager& obj) = delete;

    template<typename T>
    T getPropOrDefault(const std::string &category, const std::string &group, const std::string &key, T defaultValue);

    void refreshValues();
    void reInit();
private:
    PropertiesManager();
    ~PropertiesManager();

    static inline std::shared_ptr<PropertiesManager> instance;
    static inline std::mutex instanceLock;
    std::map<std::string, std::shared_ptr<PropertiesCategory>> categoriesMap;

    void iterateDirectoriesForTomlFiles(const std::filesystem::path &path);
    static void addDirectoryPaths(const std::filesystem::path &path, std::vector<std::string> *directoryPaths) ;
    void createNewPropertiesCategory(const std::string &category);
    void initPropertyManager();

    class PropertiesCategory
    {
    public:
        explicit PropertiesCategory(const std::string& path);
        ~PropertiesCategory();

        template<typename T>
        T getPropOrDefault(std::string group, std::string key, T defaultValue);
        void refreshValues();

    private:
        std::mutex dataLock;
        std::mutex fileLock;
        toml::parse_result fileParser;
        std::string path;
        bool fileUpdateRequired;

        void updateFileIfRequired();

        template<typename T>
        void insertMissingGroupAndKeys(std::string &group, const std::string &key, T defaultValue);
    };
};

template<typename T>
T PropertiesManager::getPropOrDefault(const std::string &category, const std::string &group, const std::string &key, T defaultValue)
{
    if (categoriesMap.find(category) == categoriesMap.end())
    {
        createNewPropertiesCategory(category);
    }

    return categoriesMap[category]->getPropOrDefault<T>(group, key, defaultValue);
}

template<typename T>
T PropertiesManager::PropertiesCategory::getPropOrDefault(std::string group, std::string key, T defaultValue)
{
    insertMissingGroupAndKeys(group, key, defaultValue);

    return fileParser[group][key].value_or(defaultValue);
}

template<typename T>
void PropertiesManager::PropertiesCategory::insertMissingGroupAndKeys(std::string &group, const std::string &key, T defaultValue)
{
    std::scoped_lock lock { dataLock };

    if (!fileParser.contains(group))
    {
        fileParser.insert(group, toml::table());
        fileUpdateRequired = true;
    }

    if (!fileParser[group].as_table()->contains(key))
    {
        fileParser[group].as_table()->insert(key, defaultValue);
        fileUpdateRequired = true;
    }
}

COMMON_PP_NAMESPACE_END

#endif //SLACK_JAW_PROPERTIESMANAGER_H
