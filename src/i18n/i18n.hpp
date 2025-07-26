#pragma once
#include <string>
#include <algorithm>
#include <map>
class i18n
{
    public:
    std::string language;
    i18n();
    std::string of(std::string key);
    void add(std::string key, std::string val);
    void save();
    void load();
    private:
    std::map<std::string, std::string> tr;
};
const std::string I18NPATH = "i18n:/";
const std::string FILESUFFIX = ".json";