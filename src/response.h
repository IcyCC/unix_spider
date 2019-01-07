#pragma once
#include<string>

namespace usp{
    class Response {
        
        public:
            std::string ReadHeader(std::string key); // 根据key读取http header
            std::string RawHeader(); // 裸的响应头
            std::string RawBody(); // 裸的文本信息
    };
}
