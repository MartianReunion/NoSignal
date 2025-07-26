#pragma once
#include <string>
#include <algorithm>
#include <map>
#include "log/logger.hpp"
#include "log/logManager.hpp"
class i18n
{
    public:
    inline i18n(std::string lang) {language = lang;load();};
    // 获取翻译键值
    std::string of(std::string key);
    // 数据生成：可以用代码生成翻译键值
    void add(std::string key, std::string val);
    // 保存生成的数据
    void save();
    // 获取翻译键值
    void load();
    inline std::string getlang() {return language;};
    private:
    std::map<std::string, std::string> tr;
    std::string language;
};

// 语言文件地址：i18n:/xx_xx.json e.g.:i18n:/en_us.json（英语-美国）或者i18n:/zh_jbp.json（中文-JBP口音）
const std::string I18NPATH = "i18n:/";
const std::string FILESUFFIX = ".json";

// 负责数据生成（语言文件）
class TranslationDataGen
{
    public:
    void gen();
};