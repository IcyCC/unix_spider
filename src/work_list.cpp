#include "work_list.h"


bool usp::WorkList::Put(std::string str)
{
    if(unprocessed.find(str) != unprocessed.end()){
        return false;
    }
    if(processed.find(str) != processed.end()){
        return false;
    }
    unprocessed.insert(str);
    return true;
}

std::string usp::WorkList::Get()
{
    std::string get_url;
    if (unprocessed.empty()){
        return  get_url;
    }
    for (auto it = unprocessed.begin(); it!=unprocessed.end();it++ ){
        return *it;
    }
    return get_url;
}
bool usp::WorkList::IsEmpty()
{
    if(unprocessed.empty())
    {
        return true;
    }
    return false;
}