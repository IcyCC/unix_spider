#pragma once
#include<string>

namespace usp{
    class Response {
        
        public:
            int status;
            std::map<std::string, std::string> header;
            std::string raw;
            std::string body;

            std::string ReadHeader(std::string key); // ����key��ȡhttp header
            std::string GetRawHeader(); // �����Ӧͷ
            std::string GetRaw(); // ����ı���Ϣ
    };
}
