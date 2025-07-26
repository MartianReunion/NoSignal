#include <iostream>
#include "filemanager/filemanager.hpp"
#include "i18n/i18n.hpp"
#include "uuid/uuid.hpp"
int main()
{
    std::cout << "Hello World!" << std::endl;
    std::fstream fst;
    FileManager().getfile("GaMeDaTa:/TesT.tXt",fst,NORMAL);
    std::string hhh;
    fst >> hhh;
    std::cout << hhh << std::endl;
    fst.close();
    i18n english("en_us");
    i18n chinese("zh_cn");
    // chinese.add("nosignal.welcome","你好");
    // chinese.save();
    i18n russian("ru_ru");
    // russian.add("nosignal.welcome","привет");
    // russian.save();
    // english.add("nosignal.welcome", "Hello");
    // english.save();
    english.load();
    chinese.load();
    russian.load();
    std::cout << english.of("nosignal.welcome") << std::endl;
    std::cout << chinese.of("nosignal.welcome") << std::endl;
    std::cout << russian.of("nosignal.welcome") << std::endl;
    std::cout << UUID().toString() << std::endl;
    std::cout << UUID().toString2() << std::endl;
    UUID u;
    for(auto i = u.getData().begin();i != u.getData().end();i++)
    {
        std::cout << static_cast<int>(*i) << " ";
    }
    std::cout << std::endl;
    return 0; 
}