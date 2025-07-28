#pragma once
#include <string>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <vector>
#include <functional>
#include <iostream>
const std::string GAMEDIRROOT = "./";
const std::ios::openmode BINARY = std::ios::in | std::ios::out | std::ios::binary;
const std::ios::openmode NORMAL = std::ios::in | std::ios::out;
const std::ios::openmode NORMALTRUNC = std::ios::in | std::ios::out | std::ios::trunc;
const std::ios::openmode BINARYTRUNC = std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc;
std::string to_upper(std::string x);
std::string to_lower(std::string x);
class FileManager
{
    public:
    bool getfile(std::string path, std::fstream &s, std::ios::openmode way);
    bool getfile_auto(std::string path, std::fstream &s, std::ios::openmode way);
    bool existfile(std::string path);
    bool existdir(std::string path);

    //$判断路径是否是转换后的*#1路径
    bool isconverted(std::string path);

    //$转换路径格式，转换失败返回GAMEDIRROOT，注意如果你把已经转换的输进去也会转换失败*#1待转换的路径
    std::string convertpath(std::string x);

    //$获取一个目录下的所有文件并把路径装进vector里*#1目录*#2vector
    void getallfile(std::string path,std::vector<std::string> &x);

    //$对一个目录下的包括子目录的所有文件的目录进行操作*#1目录（可以为未转换的）*#2function
    void getallfile_todo(std::string path,std::function<void(std::string)> func);

    //$对一个目录下的包括子目录的所有文件的目录进行操作，由func决定是否向下遍历，true=向下*#1目录（可以为未转换的）*#2function
    void getallfile_todo_byhand(std::string path,std::function<bool(std::string)> func);

    static void print(std::string x) { std::cout << x <<std::endl; }
    static bool print_byhand(std::string x) { std::cout << x <<std::endl; return true;}
};
// FileManager FILEMANAGER = FileManager();
