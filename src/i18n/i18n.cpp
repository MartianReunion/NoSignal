#include "i18n/i18n.hpp"
#include "filemanager/filemanager.hpp"
#include <fstream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
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
    if(fm.getfile(I18NPATH + language + FILESUFFIX, f, NORMAL))
    {
        json j;
        f >> j;
        f.close();
        tr.clear();
        for(auto i=j.begin();i != j.end();i++)
        {
            tr[i.key()]=i.value();
        }
    }
}
void i18n::save()
{
    FileManager fm = FileManager();
    std::fstream f;
    if(fm.getfile_auto(I18NPATH + language + FILESUFFIX, f, NORMALTRUNC))
    {
        json j(tr);
        f << j;
        f.close();
    }
}

void TranslationDataGen::gen()
{
    i18n EN_US("en_us");
    EN_US.add("nosignal.hello","hello");
    EN_US.save();
}