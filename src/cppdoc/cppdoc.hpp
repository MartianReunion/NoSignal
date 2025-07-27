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
    bool iscomment(std::string x);
    // bool isfunc(std::string x);
    bool isclass(std::string x);
    std::vector<std::string> getnames(std::string x);
    bool isgood(char ch);
    std::string getbetween(std::string x,std::string l,std::string r);
    std::string substring(std::string x,int l,int r);
    std::string getbetween_auto(std::string x,std::string l,std::string r);
    std::string getclass(std::string x);
};

const std::string DOCSUFFIX = ".md";
const std::string CLASS = "class ";