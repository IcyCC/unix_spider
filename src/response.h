#pragma once
#include<string>
#include <map>

namespace usp{
    class Response {
        
        public:
            int status;
            std::map<std::string, std::string> header;
            std::string raw;
            std::string body;

            std::string ReadHeader(std::string key); // 根据key读取http header
            std::string RawHeader(); // 裸的响应头
            std::string RawBody(); // 裸的文本信息
    };
}
