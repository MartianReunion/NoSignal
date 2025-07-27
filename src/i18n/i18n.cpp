#include "i18n/i18n.hpp"
#include "filemanager/filemanager.hpp"
#include <fstream>
#include "nlohmann/json.hpp"
#include "i18n/utiles.hpp"
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
    EN_US.add("nosignal.cppdoc.func", "## Function ");
    EN_US.add("nosignal.cppdoc.desc", "**Description:** ");
    EN_US.add("nosignal.cppdoc.para", "**Parameter** ");
    EN_US.add("nosignal.cppdoc.colon", " : ");
    EN_US.add("nosignal.cppdoc.class", "# Class ");
    EN_US.save();

    i18n FR_FR("fr_fr");
    FR_FR.add("nosignal.hello","bonjour");
    FR_FR.add("nosignal.cppdoc.func", "## Fonction ");
    FR_FR.add("nosignal.cppdoc.desc", "**Description:** ");
    FR_FR.add("nosignal.cppdoc.para", "**Paramètre** ");
    FR_FR.add("nosignal.cppdoc.colon", " : ");
    FR_FR.add("nosignal.cppdoc.class", "# Classe ");
    FR_FR.save();

    i18n DE_DE("de_de");
    DE_DE.add("nosignal.hello","hallo");
    DE_DE.add("nosignal.cppdoc.func", "## Funktion ");
    DE_DE.add("nosignal.cppdoc.desc", "**Beschreibung:** ");
    DE_DE.add("nosignal.cppdoc.para", "**Parameter** ");
    DE_DE.add("nosignal.cppdoc.colon", " : ");
    DE_DE.add("nosignal.cppdoc.class", "# Klasse ");
    DE_DE.save();

    // 还没找到支持中文的方法，只能先支持一下法语和德语，但是是机翻
    // i18n ZH_CN("zh_cn");
    // ZH_CN.add("nosignal.hello",gbktoutf8("你好"));
    // ZH_CN.add("nosignal.cppdoc.func", gbktoutf8("## 方法 "));
    // ZH_CN.add("nosignal.cppdoc.desc", gbktoutf8("**描述:** "));
    // ZH_CN.add("nosignal.cppdoc.para", gbktoutf8("**参数** "));
    // ZH_CN.add("nosignal.cppdoc.colon", gbktoutf8(" : "));
    // ZH_CN.add("nosignal.cppdoc.class", gbktoutf8("# 类 "));
    // ZH_CN.save();

    // 整活语言：村民语-MC
    i18n VL_MC("vl_mc");
    VL_MC.add("nosignal.hello","heng");
    VL_MC.add("nosignal.cppdoc.func", "## hengheng hengheng ");
    VL_MC.add("nosignal.cppdoc.desc", "**henghengheng:** ");
    VL_MC.add("nosignal.cppdoc.para", "**hengheng hengheng heng** ");
    VL_MC.add("nosignal.cppdoc.colon", " : ");
    VL_MC.add("nosignal.cppdoc.class", "# heng heng henghengheng hengheng ");
    VL_MC.save();
}