#pragma once

#include <string>
#include <functional>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <iterator>
#include "util.h"


namespace usp {


    class Parser {
    private:
        std::list<char> l_raw_body;// 裸的文本部分
        std::string raw_body;
        std::string raw_text;
        std::string raw_header;

        const int C_DISTANCE = 500;
        const float C_LIMIT = 0.4;

        std::string getRawBodyStr(){
            std::string res;
            for(auto i : l_raw_body){
                res.push_back(i);
            }
            return res;
        };

    public:
        std::string body; //正文
        std::map<std::string, std::string> header;
        std::string title;

        Parser(std::string raw); // 构造
        Parser(){};
        ~Parser() {
        };

        bool ParseMainBody();
        bool ParseHeader();


        std::string GetMainBody(); // 获取正文
        std::string GetTitle() {
            return title;
        };
        std::string ReadMeta(std::string key){
            auto r = header.find(key);
            if(r==header.end()){
                return "";
            } else {
                return r->second;
            }
        }; //读meta
        std::vector<std::string> GetAllUrls();

    };

}
