#include "work_list.h"


std::vector<std::string> unique_element_in_vector(std::vector<std::string> v)
{
	std::vector<std::string>::iterator vector_iterator;
	vector_iterator = unique(v.begin(),v.end());
	if(vector_iterator != v.end()){
		v.erase(vector_iterator,v.end());
	}
	return v;
}

bool usp::WorkList::Put(std::string str)
{
    for(int i =  0; i < unprocessed.size(); i++){
        if(unprocessed[i] == str)
            return false;
    }
    for(int i =  0; i < processed.size(); i++){
        if(processed[i] == str)
            return false;
    }
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
    if(unprocessed.empty())
    {
        return true;
    }
    return false;
}