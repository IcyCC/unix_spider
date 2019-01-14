#include "parser.h"
#include <string>

usp::Parser::Parser(std::string raw) {
    raw_text = raw;

    auto  body_begin = raw.find("<body");
    auto body_end = raw.rfind("/body>");
    if(body_begin!=std::string::npos && body_end != std::string::npos){
        raw_body = raw.substr(
                body_begin,
                body_end
        );
    }

    for (auto i : raw_body) {
        l_raw_body.push_back(i);
    }

    auto  header_begin = raw.find("<head");
    auto header_end = raw.rfind("/head>");

    if(header_begin!=std::string::npos && header_end != std::string::npos){
        raw_header = raw.substr(
                header_begin,
                header_end
        );
    }
}


std::string usp::Parser::GetMainBody() {
    return body;
}

bool usp::Parser::ParseMainBody() {

    // 1.step 去除 <! **> <div> <DIV>
    std::string token; // 缓存当前读到的token
    std::vector<std::list<char>::iterator> wait_delete_stack;
    std::vector<std::list<char>::iterator> sure_delete_stack;

    for (auto it = l_raw_body.begin(); it != l_raw_body.end(); it++) {
        char item = *(it);
        if (IsBeginWith(token, "<!-")) {
            if (IsEndWith(token, "->")) {
                token.clear();
                while (!wait_delete_stack.empty()) {
                    auto i = wait_delete_stack.back();
                    sure_delete_stack.push_back(i);
                    wait_delete_stack.pop_back();
                }
            }
        } else if (IsBeginWith(token, "/*")) {
            if (IsEndWith(token, "*/")) {
                token.clear();
                while (!wait_delete_stack.empty()) {
                    auto i = wait_delete_stack.back();
                    sure_delete_stack.push_back(i);
                    wait_delete_stack.pop_back();
                }
            }
        } else if ((IsBeginWith(token, "<div") || IsEndWith(token, "<DIV")) && token.back() == '>') {
            token.clear();
            while (!wait_delete_stack.empty()) {
                auto i = wait_delete_stack.back();
                sure_delete_stack.push_back(i);
                wait_delete_stack.pop_back();
            }
        } else if (token == "</div>" || token == "</DIV>") {
            token.clear();
            while (!wait_delete_stack.empty()) {
                auto i = wait_delete_stack.back();
                sure_delete_stack.push_back(i);
                wait_delete_stack.pop_back();
            }
        } else if (item == '<') {
            // 当不以 <! /* 为开始 说明是普通内容 遇到<清空不删除 直接清除
            token.clear();
            wait_delete_stack.clear();
        }
        token.push_back(item);
        wait_delete_stack.push_back(it);
    };

    while (!sure_delete_stack.empty()) {
        auto i = sure_delete_stack.back();
        l_raw_body.erase(i);
        sure_delete_stack.pop_back();
    }

    // 2.文本密度计算
    int ch_offset = 0; // 标记字符偏移量
    int block_offset = 0; // 记录块便宜
    int text_weights[9000] = {0}; // 存储文本数量
    bool tag_flag = false; // 标志是否处在标签内部

    for (auto it = l_raw_body.cbegin(); it != l_raw_body.cend(); it++) {
        ch_offset++;
        char item = *(it);
        if (item == '<') {
            // 当看到标签开始符号 并且处于 非标签标记状态
            tag_flag = true;
        }

        if (!tag_flag) {
            text_weights[block_offset]++;
        }

        if (item == '>') {
            // 标签结束时退出标签态
            tag_flag = false;
        }
        if (ch_offset % C_DISTANCE == 0) {
            // 到达一个 块末尾
            block_offset++;
        }
    }

    // 3. 找出最长大于阈值区间 text_weight[max_index-thr_record[max_index]]:text_weight[max_index]
    int thr_record[3000] = {0};
    int max_index = 0;
    int max_value = 0;
    for (int i = 0; i <= block_offset; i++) {
        if (text_weights[i] > C_LIMIT){
            // 大于阈值当前为前一个阈值加1
            thr_record[(i + 1)] = thr_record[i] + 1;

            if (thr_record[i + 1] > max_value) {
                max_index = i;
                max_value = thr_record[i + 1];
            }
        }
    }

    auto pre = getRawBodyStr();
    int start_pos = (max_index-thr_record[max_index]) * C_DISTANCE;
    int end_pos = max_index * C_DISTANCE;
    int mid_pos = ((end_pos - start_pos) / 2) + start_pos;

    auto start_info = FindMaxTag2WordPos(pre, start_pos, mid_pos);
    auto end_info = FindMaxWord2TagPos(pre, mid_pos, end_pos);
    // 找开始点

    body = DropTag(pre.substr(start_info.first, end_info.first));
    body = Trim(body);
    return true;
}

bool usp::Parser::ParseHeader() {
    enum class ReadHeaderStatus {
        NONE,
        META_TAG,
        TITLE,
    };
    ReadHeaderStatus status = ReadHeaderStatus::NONE; // 0 非tag内容 1 处于 mata tag 中 2 处于title tag中
    std::string token;
    for (auto i : raw_header) {
        if (status == ReadHeaderStatus::NONE && i == '<') {
            // 当前不在tag内部 并且发现进入tag标志清空
            token.clear();
        }
        token.push_back(i);

        // 根据 当前状态进入新的状态
        if (status == ReadHeaderStatus::NONE && (token == "<meta" || token == "<META")) {
            // meta标签开始
            status = ReadHeaderStatus::META_TAG;
        } else if (status == ReadHeaderStatus::NONE && token == "<title>") {
            // 开始于标签
            status = ReadHeaderStatus::TITLE;
            token.clear();
        } else if (status == ReadHeaderStatus::TITLE && i == '<') {
            // 认为标题结束
            status = ReadHeaderStatus::NONE;
            token.clear();
        } else if (status == ReadHeaderStatus::TITLE) {
            // 处于标题标签内
            title.push_back(i);
        } else if (status == ReadHeaderStatus::META_TAG && i == '>') {
            // meta标签结束 进行解析
            header.insert(ParseMeta(token));
            token.clear();
            status = ReadHeaderStatus::NONE;
        }
    }
    title = CleanString(title);
    return true;
}


std::vector<std::string> usp::Parser::GetAllUrls() {

    enum class UrlParseStatus {
        NONE,
        URL,
    };

    auto res = std::vector<std::string>();
    UrlParseStatus status = UrlParseStatus::NONE;
    std::string token;
    for (auto i : raw_text) {
        if (i == ' ') {
            token.clear();
        } else {
            token.push_back(i);
        }

        if (status == UrlParseStatus::NONE && token == "href=\"") {
            status = UrlParseStatus::URL;
            token.clear();
        } else if (status == UrlParseStatus::URL && i == '"') {
            token.pop_back();
            if (!IsBeginWith(token, "java")){
                res.push_back(token);
            }
            token.clear();
            status = UrlParseStatus::NONE;
        }
    }
    return res;
}

