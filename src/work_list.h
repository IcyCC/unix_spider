#pragma once
#include<string>
#include<vector>
#include <algorithm> 
#include <iterator>
#include <set>
#include <cstdio>
namespace usp{
    class WorkList {
        public:
            bool Put(std::string v);
            std::string Get(); 
            bool IsEmpty();
            std::set<std::string > unprocessed;   //未处理的url
            std::set<std::string> processed;     //已处理的url
    };
}
