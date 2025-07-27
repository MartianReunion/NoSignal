#pragma once
#include <string>
#include "filemanager/filemanager.hpp"
#include "i18n/i18n.hpp"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
class CppDoc
{
    public:
    inline void gendoc_auto(std::string path) {gendoc(path, i18n("en_us"));}
    void gendoc(std::string path,i18n lang);
    void gendoc_all(std::string path,i18n lang);
    inline void gendoc_all_auto(std::string path) {gendoc_all(path, i18n("en_us"));}
    bool iscomment(std::string x);
    // bool isfunc(std::string x);
    bool isclass(std::string x);
    std::vector<std::string> getnames(std::string x);
    bool isgood(char ch);
    std::string getbetween(std::string x,std::string l,std::string r);
    std::string substring(std::string x,int l,int r);
    std::string getbetween_auto(std::string x,std::string l,std::string r);
    std::string getclass(std::string x);
    bool skipon(std::string x);
    bool skipoff(std::string x);
};

const std::string DOCSUFFIX = ".md";
const std::string CLASS = "class ";
const std::string TITLE_LEVELS[7] = {"","# ","## ","### ","#### ","##### ","###### "};
const std::string QUOTE = ">";
const std::string BOLD = "**";
const std::string CODE = "`";
const std::string DELETELINE = "~~";

class MarkdownFormat
{
    public:
    std::string title(std::string x, int y);
    std::string bold(std::string x);
    std::string deleteline(std::string x);
    std::string code(std::string x);
    std::string quote(std::string x);
};