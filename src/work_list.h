#pragma once
#include<string>

namespace usp{
    class WorkList {
        public:
            bool Put(std::string v);
            std::string Get();
            bool IsEmpty();
    };
}
