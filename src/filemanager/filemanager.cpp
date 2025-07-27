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

bool FileManager::getfile(std::string path, std::fstream &s, std::ios::openmode way)
{
    std::string cpath = isconverted(path) ? path : convertpath(path);
    if(!existfile(cpath))
    {
        return false;
    }
    s.open(cpath, way);
    return s.good();
}

bool FileManager::getfile_utf8(std::string path, std::wfstream &s, std::ios::openmode way)
{
    std::string cpath = isconverted(path) ? path : convertpath(path);
    if(!existfile(cpath))
    {
        return false;
    }
    s.open(cpath, way);
    s.imbue(utf8);
    return s.good();
}

bool FileManager::getfile_auto(std::string path, std::fstream &s, std::ios::openmode way)
{
    std::string cpath = isconverted(path) ? path : convertpath(path);
    if(!fs::exists(cpath))
    {
        fs::path dirpath = fs::path(cpath).parent_path();
        if(!existdir(dirpath.string()))
        {
            fs::create_directories(dirpath);
        }
    }
    s.open(cpath, way);
    return s.good();
}

bool FileManager::getfile_auto_utf8(std::string path, std::wfstream &s, std::ios::openmode way)
{
    std::string cpath = isconverted(path) ? path : convertpath(path);
    if(!fs::exists(cpath))
    {
        fs::path dirpath = fs::path(cpath).parent_path();
        if(!existdir(dirpath.string()))
        {
            fs::create_directories(dirpath);
        }
    }
    s.open(cpath, way);
    s.imbue(utf8);
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

void FileManager::getallfile(std::string path,std::vector<std::string> &x)
{
    std::string cpath = isconverted(path) ? path : convertpath(path);
    for(auto& i : fs::directory_iterator(cpath))
    {
        fs::path pt = i.path();
        if(fs::is_directory(i))
        {
            getallfile(pt.string(),x);
        }
        else
        {
            x.push_back(pt.string());
        }
    }
}