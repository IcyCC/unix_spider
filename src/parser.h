#pragma once

#include<string>
#include <functional>
#include <vector>
#include <map>
#include "util.h"


namespace usp {


    class BoolString {
    private:
        std::string str;
        bool *pBoolean;
    private:
        void resetBoolean() {
            for (int i = 0; i < int(str.length()); i++) {
                pBoolean[i] = true;
            }
        };
    public:
        BoolString(std::string s) {
            str = s;
            pBoolean = new bool(int(str.length()));
            resetBoolean();
        }

        ~BoolString() {
            delete pBoolean;
        }

        std::string toStr() {
            std::string r_str;
            for (int i = 0; i < int(str.length()); i++) {
                if (pBoolean[i]) {
                    r_str.push_back(str[i]);
                }
            }
            return r_str;
        }


        void ForEach(std::function<void(int index, int r_index, char item, BoolString *bs)> f); // 用于遍历

        int Delete(int index) {
            pBoolean[index] = false;
            return 0;
        }
        // 用于删除特定下标的字符
    };



    class Parser {
    private:
        BoolString *raw_body = NULL;// 裸的文本部分
        std::string raw_text;
        std::string raw_header;

        const int C_DISTANCE = 200;
        const float C_LIMIT = 0.6;

    public:
        std::string body; //正文
        std::map<std::string, std::string> header;
        std::string title;

        Parser(std::string raw); // 构造
        Parser(){};
        ~Parser() {
                delete raw_body;
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
