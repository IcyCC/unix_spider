#pragma once
#include<string>

namespace usp{
    class Response {
        
        public:
            int status;
            std::map<std::string, std::string> header;
            std::string raw;
            std::string body;

            std::string ReadHeader(std::string key); // 根据key读取http header
            std::string GetRawHeader(); // 裸的响应头
            std::string GetRaw(); // 裸的文本信息
    };
}
