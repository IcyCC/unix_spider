#include "data.h"

usp::Data Loads(std::string path)
{
    usp::Data data;
    ifstream infile(path);
    if(!infile)
    {
        cout <<"open file error !"<<endl;
        getchar();
        return false;
    }
    //file.read((char *)&data,sizeof(string));

    infile >> data.title >> data.author >> data.body;
    infile.close()
    return data;
}

bool usp::Load(std::string str) //从字符串加载
{
    usp::Data data;
    std::vector<std::string> res;
    if("" == string)    return false;
    char *strs = new char[str.length() + 1];
    strcpy(strs,str.c_str());

    const std::string delim = " "; //分割的字符标准
    char *d = new char[delim.length() + 1];
    strcpy(d,delim.c_str());

    char *p = strtok(strs,d);
    while(p)
    {
        std::string s = p;
        res.pusk_back(s);
        p = strtok(NULL,d);
    }

    data.title = res[0];
    data.author = res[1];
    data.body = res[2];

    return true;
}

std::string usp::Dump() //生成字符串
{
    usp::Data data;
    std::string str;
    str = data.title + " " + data.author + " " + data.body;
    return str;
}

bool usp::Dumps (std::string path)// 写入到文件
{
    usp::Data data;
    fstream infile(path,ios::in | ios::bindary)
    if(!infile)
    {
        cout <<"open file error !"<<endl;
        getchar();
        return false;
    }
    infile.write((char *)&data,sizeof(data));
    infile.close();
    return true;
}