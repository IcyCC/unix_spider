#include "parser.h"

#include <string>


void usp::BoolString::ForEach(std::function<void(int index, int r_index, char item, BoolString *bs)> f) {
    int i = 0;
    for (int r_i = 0; r_i < str.length(); r_i++) {
        if (pBoolean[i]) {
            f(i, r_i, str[i], this);
            i++;
        }
    }
}

usp::Parser::Parser(std::string raw) {
    raw_text = raw;
    raw_body = new BoolString(raw.substr(
            raw.find("<body"),
            raw.rfind("/body>")
    ));
}


std::string usp::Parser::GetMainBody() {
    return body;
}

bool usp::Parser::ParseMainBody() {

    // 1.step 去除 <! **> <div> <DIV>
    std::string token; // 缓存当前读到的token
    std::vector<int> wait_delete_stack;
    raw_body->ForEach([&](int index, int r_index, char item, BoolString *bs) {
        if (IsBeginWith(token, "<!")) {
            if (IsEndWith(token, "!>")) {
                token.clear();
                while (!wait_delete_stack.empty()) {
                    int i = wait_delete_stack.back();
                    bs->Delete(i);
                    wait_delete_stack.pop_back();
                }
            }
        } else if (IsBeginWith(token, "/*")) {
            if (IsEndWith(token, "*/")) {
                token.clear();
                while (!wait_delete_stack.empty()) {
                    int i = wait_delete_stack.back();
                    bs->Delete(i);
                    wait_delete_stack.pop_back();
                }
            }
        } else if (item == '<') {
            // 当不以 <! /* 为开始 说明是普通内容 遇到<清空不删除 直接清除
            token.clear();
            wait_delete_stack.clear();
        } else if (token == "<div>" || token == "<DIV>" || token == "</div>" || token == "</DIV>") {
            token.clear();
            while (!wait_delete_stack.empty()) {
                int i = wait_delete_stack.back();
                bs->Delete(i);
                wait_delete_stack.pop_back();
            }
        }
        token.push_back(item);
        wait_delete_stack.push_back(r_index);
    });

    // 2.
    return false;
}