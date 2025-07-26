#include <iostream>
#include "filemanager/filemanager.hpp"
int main()
{
    std::cout << "Hello World!" << std::endl;
    std::fstream fst;
    FileManager().getfile("GaMeDaTa:/TesT.tXt",fst,NORMAL);
    std::string hhh;
    fst >> hhh;
    std::cout << hhh << std::endl;
    fst.close();
    return 0; 
}