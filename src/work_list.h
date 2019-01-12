#pragma once
#include<string>

namespace usp{
    class WorkList {
        public:
            bool put(std::string v);
            std::string get(); 
            bool is_empty();
            std::vector<std::string> unprocessed;   //未处理的url
            std::vector<std::string> processed;     //已处理的url
    };
}
