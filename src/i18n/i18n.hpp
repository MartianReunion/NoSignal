#pragma once
#include <string>
#include <algorithm>
#include <map>
#include "log/logger.hpp"
#include "log/logManager.hpp"
class i18n
{
    public:
    inline i18n(std::string lang) {language = lang;};
    std::string of(std::string key);
    void add(std::string key, std::string val);
    void save();
    void load();
    inline std::string getlang() {return language;};
    private:
    std::map<std::string, std::string> tr;
    std::string language;
};
const std::string I18NPATH = "i18n:/";
const std::string FILESUFFIX = ".json";