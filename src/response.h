#pragma once

#include<string>
#include <map>
#include "util.h"

namespace usp {
    class Response {
    private:
        std::string raw;
        std::string raw_meta;
        std::string raw_header;
        std::map<std::string, std::string> header;

    public:
        int status;
        std::string body;
        Response(const std::string& _raw){
            raw = _raw;
            // 解析body
            unsigned long pos=raw.find("\r\n\r\n");
            if (pos != std::string::npos) {
                body = raw.substr(pos+4);
            }
            unsigned long pos_header=raw.find("\r\n");
            if (pos != std::string::npos) {
                raw_header = raw.substr(pos_header+2, pos - pos_header);
                raw_meta =  raw.substr(0, pos_header);
            }

            status = ParseResponseMeta(raw_meta);
            // 解析header
            header = ParseHttpHeader(raw_header);
        }
        std::string ReadHeader(std::string key); // 根据key读取http header
        std::string GetRawHeader(); // 裸的响应头
        std::string GetRaw(); // 裸的文本信息
    };
}
