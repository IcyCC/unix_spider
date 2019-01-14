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
namespace usp{
    class Request {
        private: 
            std::string url;
            std::string method;
            std::string header;
        public:
            usp::Response Fetch(); //爬取
            bool SetHeader(std::string header);//设置http的header的文本
    };
}
