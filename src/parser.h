#pragma once

#include<string>
#include <functional>
#include <vector>
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
        BoolString *raw_body;// 裸的文本部分
        std::string raw_text;

        const int C_DISTANCE = 200;
        const float C_LIMIT = 0.6;

    public:
        std::string body; //正文
        Parser(std::string raw); // 构造
        ~Parser() {
            delete raw_body;
        };

        bool ParseMainBody();


        std::string GetMainBody(); // 获取正文
        std::vector<std::string> GetAllUrls();

        std::string GetAuthor(); // 获取作者
        std::string CommFind(); //通用查找

    };
}
