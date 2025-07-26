#pragma once
#include <string>
#include <filesystem>
#include <algorithm>
#include <fstream>
const std::string GAMEDIRROOT = "./";
const int BINARY = std::ios::in || std::ios::out || std::ios::binary;
const int NORMAL = std::ios::in || std::ios::out;
std::string to_upper(std::string x);
std::string to_lower(std::string x);
class FileManager
{
    public:
    bool getfile(std::string path, std::fstream &s, std::ios::openmode way);
    bool existfile(std::string path);
    bool existdir(std::string path);
    // void MakeGameDir();
    bool isconverted(std::string path);
    std::string convertpath(std::string x);
};
// FileManager FILEMANAGER = FileManager();
