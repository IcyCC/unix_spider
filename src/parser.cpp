#include "parser.h"

#include <string>

void usp::BoolString::ForEach(std::function<void(int index, int r_index, char item, usp::BoolString *bs)> f) {
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

    // 2.文本密度计算
    int ch_offset = 0; // 标记字符偏移量
    int block_offset = 0; // 记录块便宜
    int text_weights[1000] = {0}; // 存储文本数量
    float tag_flag = false; // 标志是否处在标签内部

    raw_body->ForEach([&](int index, int r_index, char item, BoolString *bs) {
        ch_offset++;
        if (item == '<') {
            // 当看到标签开始符号 并且处于 非标签标记状态
            tag_flag = true;
        }

        text_weights[block_offset] = text_weights[block_offset] + tag_flag ? 1 : 0;

        if (item == '>') {
            // 标签结束时退出标签态
            tag_flag = false;
        }
        if (ch_offset % C_DISTANCE == 0) {
            // 到达一个 块末尾
            block_offset++;
        }
    });

    // 3. 找出最长大于阈值区间 text_weight[max_index-thr_record[max_index]]:text_weight[max_index]
    int thr_record[1000] = {0};
    int max_index = 0;
    int max_value = 0;
    for (int i = 0; i <= block_offset; i++) {
        if (float(text_weights[i])/C_DISTANCE > C_LIMIT){
            // 大于阈值当前为前一个阈值加1
            thr_record[i + i] = thr_record[i] + 1;
            if (thr_record[i + i] > max_value) {
                max_index = i;
                max_value = thr_record[i + i];
            }
        }
    }

    auto pre_body = usp::BoolString(raw_body->toStr().substr((max_index - thr_record[max_index]) * C_DISTANCE,
                                                   thr_record[max_index] * C_DISTANCE));
    body = pre_body.toStr();
    return true;
}