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
    // 英语-美国
    // EN_US.add("nosignal.logger.is_not_running", "Logging system is not running");
    // EN_US.add("nosignal.logmanager.name", "LogManager");
    // EN_US.add("nosignal.logmanager.failed_to_open_file", "Failed to open log file");
    // EN_US.add("nosignal.network.message.must_be_a_subtype", "TMessageSubtype must be a subtype of Network::Message");

    // 中文-中国
    // ZH_CN.add("nosignal.logger.is_not_running", "日志系统不在运行");
    // ZH_CN.add("nosignal.logmanager.name","日志管理器");
    // ZH_CN.add("nosignal.logmanager.failed_to_open_file", "打开日志文件失败");
    // ZH_CN.add("nosignal.network.message.must_be_a_subtype", "TMessageSubtype 必须是 Network::Message 的子类型");

    // 中文-JBP口音
    // ZH_JBP.add("nosignal.logger.is_not_running","日志xiei统不寨yung行");
    // ZH_JBP.add("nosignal.logmanager.name","日志管腻器");
    // ZH_JBP.add("nosignal.logmanager.failed_to_open_file","打开日志weng件失败");
    // ZH_JBP.add("nosignal.network.message.must_be_a_subtype","TMessageSubtype 必须是 Network::Message 的质nuei型");
}