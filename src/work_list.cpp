#include "work_list.h"

bool usp::WorkList::Put(std::string str)
{
    unprocessed.push_back(str);
    return true;
}

std::string usp::WorkList::Get()
{
    std::string get_url;
    get_url = unprocessed.back();    //获取最后一个元素
    processed.push_back(get_url);    //放入已处理url中
    unprocessed.pop_back();         //从未处理url中删除获取
    return get_url;
}
bool usp::WorkList::IsEmpty()
{
    if(unprocessed.empty());
        return true;
    return false;
}