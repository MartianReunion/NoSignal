#include <iostream>
#include "filemanager/filemanager.hpp"
#include "i18n/i18n.hpp"
#include "uuid/uuid.hpp"
int main()
{
    std::cout << "Hello World!" << std::endl;
    TranslationDataGen().gen();
    std::fstream fst;
    FileManager().getfile("GaMeDaTa:/TesT.tXt",fst,NORMAL);
    std::string hhh;
    fst >> hhh;
    std::cout << hhh << std::endl;
    fst.close();

    std::cout << UUID().toString() << std::endl;
    std::cout << UUID().toString2() << std::endl;
    UUID u;
    for(auto i = u.getData().begin();i != u.getData().end();i++)
    {
        std::cout << static_cast<int>(*i) << " ";
    }
    std::cout << std::endl;

    std::cout << i18n("en_us").of("hello") << std::endl;
    return 0; 
}