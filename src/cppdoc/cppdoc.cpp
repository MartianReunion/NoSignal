#include "cppdoc/cppdoc.hpp"
namespace fs = std::filesystem;
bool CppDoc::iscomment(std::string x)
{
    return x.find("//") != x.npos;
}

bool CppDoc::isclass(std::string x)
{
    return x.find(CLASS) != x.npos;
}

bool CppDoc::isgood(char ch)
{
    return (ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')||(ch>='0'&&ch<='9')||(ch=='_');
}

bool CppDoc::skipon(std::string x)
{
    return x=="//*";
}

bool CppDoc::skipoff(std::string x)
{
    return x=="//**";
}

std::string CppDoc::substring(std::string x,int l,int r)
{
    std::string em;
    em.clear();
    if(l>=x.length() || r>x.length() || l>=r)
    {
        return em;
    }
    for(int i=l;i<r;i++)
    {
        em.push_back(x[i]);
    }
    return em;
}

std::string CppDoc::getbetween(std::string x,std::string l,std::string r)
{
    std::string em;
    em.clear();
    int ll=x.find(l),rr=x.find(r,ll);
    if(ll==x.npos || rr==x.npos)
    {
        return em;
    }
    return substring(x,ll+l.length(),rr);
}

std::string CppDoc::getbetween_auto(std::string x,std::string l,std::string r)
{
    std::string em;
    em.clear();
    int ll=x.find(l),rr=x.find(r,ll);
    if(ll==x.npos)
    {
        return em;
    }
    if(rr==x.npos)
    {
        std::cout << substring(x,ll+l.length(),x.length()) << std::endl;
        return substring(x,ll+l.length(),x.length());
    }
    std::cout << substring(x,ll+l.length(),rr) << std::endl;
    return substring(x,ll+l.length(),rr);
}

std::vector<std::string> CppDoc::getnames(std::string x)
{
    std::vector<std::string> rt;
    rt.clear();
    int bk = x.find('('),cbk=x.find(')'),len=x.length();
    if(bk == x.npos || cbk == x.npos || (cbk < bk))
    {
        return rt;
    }
    std::string be,af;
    for(int i=bk-1;i>=0;i--)
    {
        if(isgood(x[i]))
        {
            be.push_back(x[i]);
        }
        else
        {
            if(!be.empty())
            {
                std::reverse(be.begin(),be.end());
                rt.push_back(be);
                break;
            }
        }
    }
    if(rt.empty())
    {
        return rt;
    }
    bool flag=false;
    for(int i=bk;i<=cbk;i++)
    {
        if(x[i]==' ')
        {
            flag=true;
            continue;
        }
        if(x[i]==','||x[i]==')')
        {
            if(!af.empty())
            {
                rt.push_back(af);
                af.clear();
                flag=false;
            }
        }
        if(flag)
        {
            af.push_back(x[i]);
        }
    }
    return rt;
}

std::string CppDoc::getclass(std::string x)
{
    int bp = x.find(CLASS);
    return substring(x,bp+CLASS.length(),x.length());
}

void CppDoc::gendoc(std::string path,i18n lang)
{
    FileManager fm;
    std::fstream f;
    if(!fm.getfile(path,f,NORMAL))
    {
        return;
    }
    std::string x[2]={"",""};
    std::string cppname = fs::path(path).filename().string();
    int i=0;
    std::fstream doc;
    if(!fm.getfile_auto("cppdoc:/" + cppname + DOCSUFFIX,doc,NORMALTRUNC))
    {
        return;
    }
    bool skip=false;
    while(std::getline(f,x[i]))
    {
        if(skipon(x[i]))
        {
            skip=true;
        }
        if(skipoff(x[i]))
        {
            skip=false;
        }
        if(skip)
        {
            continue;
        }
        if(isclass(x[i]))
        {
            doc << lang.of("nosignal.cppdoc.class") << getclass(x[i]) << std::endl;
            doc << std::endl;
        }
        if(i==1)
        {
            if(iscomment(x[0]))
            {
                std::vector<std::string> nm = getnames(x[1]);
                if(nm.size()>=1)
                {
                    std::string desc = getbetween_auto(x[0],"$"," ");
                    doc << lang.of("nosignal.cppdoc.func") << nm[0] << std::endl;
                    doc << std::endl;
                    doc << lang.of("nosignal.cppdoc.desc") << desc <<std::endl;
                    doc << std::endl;
                    for(int j=1;j<nm.size();j++)
                    {
                        doc << lang.of("nosignal.cppdoc.para") << nm[j] << lang.of("nosignal.cppdoc.colon") << getbetween_auto(x[0],"#" + std::to_string(j)," ") << std::endl;
                        doc << std::endl;
                    }
                }
            }
            x[0]=x[1];
            x[1].clear();
            i=1;
            continue;
        }
        i++;
    }
}

void CppDoc::gendoc_all(std::string path,i18n lang)
{
    std::vector<std::string> all;
    all.clear();
    FileManager().getallfile(path,all);
    for(int i=0;i<all.size();i++)
    {
        gendoc(all[i],lang);
    }
}