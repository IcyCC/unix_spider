#pragma once

#include"response.h"
#include"util.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>

namespace usp {
    class Request {
    private:
        std::string url;
        std::string method;
    public:
        std::string header;
        std::map<std::string, std::string> header_map;

        Request(const std::string  _url){
            url = _url;
            method = "GET";
            auto h = std::map<std::string, std::string>();
            h.insert(std::pair<std::string, std::string>("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36"));
            h.insert(std::pair<std::string, std::string>("Connection", "close"));
            SetHeader(h);
        };

        usp::Response Fetch(); //爬取

        bool SetHeader(std::map<std::string, std::string> h);//设置http的header的文本
    };
}
