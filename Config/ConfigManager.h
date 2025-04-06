//
// Created by Adam on 06/04/2025.
//

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
#include <string>
#include <unordered_map>

class ConfigManager {
private:
    std::unordered_map<std::string, std::string> configValues;
    static ConfigManager *instance;

public:
    ConfigManager() = default;
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
    ~ConfigManager();

    static ConfigManager* getInstance();

    bool loadConfig(const std::string &filename);

    std::string getString(const std::string &key, const std::string &defaultValue = std::string());

    int getInt(const std::string &key, int defaultValue = 0);

    double getDouble(const std::string &key, double defaultValue = 0.0);

    bool getBool(const std::string &key, bool defaultValue = false);
};

#endif //CONFIGMANAGER_H
