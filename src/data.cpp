#include "data.h"
#include "util.h"

usp::Data usp::Data::Loads(std::string path)
{
    usp::Data data;
    std::ifstream infile(path);
    if(!infile)
    {
        std::cout <<"open file error !"<< std::endl;
        getchar();
        exit(0);
    }
    //file.read((char *)&data,sizeof(string));

    infile >> data.title >> data.author >> data.body;
    infile.close();
    return data;
}

bool  usp::Data::Load(std::string str) //从字符串加载
{
    usp::Data data;
    std::vector<std::string> res;
    if("" == str)    return false;
    char *strs = new char[str.length() + 1];
    strcpy(strs,str.c_str());

    const std::string delim = " "; //分割的字符标准
    char *d = new char[delim.length() + 1];
    strcpy(d,delim.c_str());

    char *p = strtok(strs,d);
    while(p)
    {
        std::string s = p;
        res.push_back(s);
        p = strtok(NULL,d);
    }

    data.title = res[0];
    data.author = res[1];
    data.body = res[2];

    delete [] d;
    delete [] strs;
    return true;
}

std::string  usp::Data::Dump() //生成字符串
{
    std::string str;
    str = title + " " + author + " " + body;
    return str;
}

bool  usp::Data::Dumps (std::string path)// 写入到文件
{
    CreateDirectory(path);
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    
    std::string narrowStr = conv.to_bytes(path.c_str()); //文件是utf8编码
    std::ofstream infile(path.c_str(),std::ios::out);
    if(!infile)
    {
        std::cout <<"open file error !"<<std::endl;
        perror("READ");
        return false;
    }
    infile << narrowStr;
    auto res = Dump();
    std::cout<<res<<std::endl;
    infile<<res.c_str();
    infile.close();
    return true;
}