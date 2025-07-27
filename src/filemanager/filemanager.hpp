#pragma once
#include <string>
#include <filesystem>
#include <algorithm>
#include <fstream>
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
    bool getfile_auto(std::string path, std::fstream &s, std::ios::openmode way); // 新增功能：如果没有就自动创建
    bool existfile(std::string path);
    bool existdir(std::string path);
    // void MakeGameDir();
    bool isconverted(std::string path);
    std::string convertpath(std::string x);
    void getallfile(std::string path,std::vector<std::string> &x);
};
// FileManager FILEMANAGER = FileManager();
