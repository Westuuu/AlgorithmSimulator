//
// Created by Adam on 06/04/2025.
//

#include "ConfigManager.h"

#include <fstream>
#include <iostream>


ConfigManager *ConfigManager::instance = nullptr;

ConfigManager *ConfigManager::getInstance() {
    if (instance == nullptr)
        instance = new ConfigManager();
    return instance;
}

bool ConfigManager::loadConfig(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening config file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        auto delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);

            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            configValues[key] = value;
        }
    }
    return true;
}

std::string ConfigManager::getString(const std::string &key, const std::string &defaultValue) {
    auto it = configValues.find(key);
    if (it != configValues.end()) {
        return it->second;
    }
    return defaultValue;
}

int ConfigManager::getInt(const std::string &key, int defaultValue) {
    auto it = configValues.find(key);
    if (it != configValues.end()) {
        try {
            return std::stoi(it->second);
        } catch (...) {
            return defaultValue;
        }
    }
    return defaultValue;
}

double ConfigManager::getDouble(const std::string &key, double defaultValue) {
    auto it = configValues.find(key);
    if (it != configValues.end()) {
        try {
            return std::stod(it->second);
        } catch (...) {
            return defaultValue;
        }
    }
    return defaultValue;
}

bool ConfigManager::getBool(const std::string &key, bool defaultValue) {
    auto it = configValues.find(key);
    if (it != configValues.end()) {
        std::string value = it->second;
        if (value == "true") {
            return true;
        } else {
            return false;
        }
    }
    return defaultValue;
}

ConfigManager::~ConfigManager() {
    delete instance;
}