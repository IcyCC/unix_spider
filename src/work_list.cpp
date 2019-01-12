#include "work_list.h"

bool usp::Put(std::string str)
{
    unprocessed.push_back(str);
    return true;
}

std::string usp::Get()
{
    std::string geturl;
    geturl = unprocessed.back();    //获取最后一个元素
    processed.push_back(geturl);    //放入已处理url中
    unprocessed.pop_back();         //从未处理url中删除获取
    return geturl;
}
bool usp::IsEmpty()
{
    if(unprocessed.empty());
        return true;
    return false;
}