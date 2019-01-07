#pragma once

#include<string>
#include <functional>


namespace usp {

    class BoolString {
    private:
        std::string str;
        bool *pBoolean;
    private:
        void resetBoolean() {
            for (int i = 0; i < str.length(); i++) {
                pBoolean[i] = true;
            }
        };
    public:
        BoolString(std::string s) {
            str = s;
            pBoolean = new bool(s.length());
            resetBoolean();
        }

        ~BoolString() {
            delete pBoolean;
        }

        std::string toStr() {
            return str;
        }

        void ForEach( std::function<void (int, char, BoolString*bs)> f); // 用于遍历

        int Delete(int index) {
            pBoolean[index] = false;
            return 0;
        }
        // 用于删除特定下标的字符
    };

    class Parser {
    private:
        BoolString *raw_text;

    public:
        std::string body; //正文
        Parser(std::string raw); // 构造
        ~Parser() {
            delete raw_text;
        };

        bool ParseMainBody();


        std::string GetMainBody(); // 获取正文
        std::vector<std::string> GetAllUrls();

        std::string GetAuthor(); // 获取作者
        std::string CommFind(); //通用查找

    };
}
