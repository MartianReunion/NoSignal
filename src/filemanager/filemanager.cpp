#include "filemanager.hpp"
namespace fs = std::filesystem;
std::string FileManager::convertpath(std::string x)
{
    int r=-1,len = x.length();
    for(int i = 0;i < len;i++)
    {
        if(x[i]==':')
        {
            r = i;
            break;
        }
    }
    if(r == -1 || r == 0 || r == len-1)
    {
        return GAMEDIRROOT;
    }
    std::string str = x.substr(0, r) + x.substr(r+1);
    return GAMEDIRROOT + to_lower(str);
}

bool FileManager::existfile(std::string path)
{
    return fs::exists(path) && (!fs::is_directory(path));
}

bool FileManager::existdir(std::string path)
{
    return fs::exists(path) && fs::is_directory(path);
}

bool FileManager::isconverted(std::string path)
{
    return path.find(':') == path.npos;
}

bool FileManager::getfile(std::string path, std::fstream &s, int way)
{
    std::string cpath = isconverted(path) ? path : convertpath(path);
    if(!existfile(cpath))
    {
        return false;
    }
    s.open(cpath, way);
    return s.good();
}

std::string to_upper(std::string x)
{
    std::string y;
    for(int i = 0;i< x.length();i++)
    {
        y.push_back(toupper(x[i]));
    }
    return y;
}

std::string to_lower(std::string x)
{
    std::string y;
    for(int i = 0;i< x.length();i++)
    {
        y.push_back(tolower(x[i]));
    }
    return y;
}