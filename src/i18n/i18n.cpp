#include "i18n/i18n.hpp"
#include "filemanager/filemanager.hpp"
#include <fstream>
std::string i18n::of(std::string key)
{
    if(tr.find(key) == tr.end())
    {
        return key;
    }
    return tr[key];
}
void i18n::add(std::string key, std::string val)
{
    tr[key]=val;
}
void i18n::load()
{
    FileManager fm = FileManager();
    std::fstream f;
    fm.getfile(I18NPATH + language + FILESUFFIX, f, NORMAL);
}