#pragma once
#include<string>
#include<vector>
#include <algorithm> 
#include <iterator> 

namespace usp{
    class WorkList {
        public:
            bool Put(std::string v);
            std::string Get(); 
            bool IsEmpty();
            std::vector<std::string> unprocessed;   //未处理的url
            std::vector<std::string> processed;     //已处理的url
    };
}
