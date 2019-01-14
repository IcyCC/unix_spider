//
// Created by 苏畅 on 2019/1/7.
// 常用的工具函数
//
#pragma once

#include <string>
#include <map>
#include <list>
#include <sstream>
#include <vector>
#include <cstring>

inline std::string delim(std::string str,std::string delim, int pos)//分割源字符、分割字符、返回容器元素位置
{
    std::vector<std::string> res;
    char *strs = new char[str.length() + 1];
    strcpy(strs,str.c_str());

    char *d = new char[delim.length() + 1];
    strcpy(d,delim.c_str());

    char *p = strtok(strs,d);
    while(p)
    {
        std::string s = p;
        res.push_back(s);
        p = strtok(NULL,d);
    }  

    delete [] strs;
    delete [] d;
    return res[pos];
}


inline bool IsAbsUrl(std::string url)
{
    //根据URL的构成，由两部分构成：<Schema>:<特定于本schema的子串> 因此,只要直接判有没有字符 ":" 就行。有：是绝对，没有相对。
    if(url.find(":") != string::npos)
        return true;
    if(url[0] != '.' && url[0] != '/')     //url第一个字符不为“.”或"/"时，为绝对路径
        return true;
    return false;
}

int GetUrlLevel(std::string url)
{
    std::vector<std::string> delim_url;
    std::string temp;
    istringstream is(url);
    //将url分割放入容器，读取容器大小，即为level
    while (std::getline(is, temp, '/')) {
        delim_url.push_back(temp);
    }
    if(url.find("//") != string::npos)
        return delim_url.size() - 1;  
    return delim_url.size(); 
}

/*返回一个二级域名*/
inline std::string GetUrlDomain(std::string url){  
    std::string domain;

    if(url.find("http://") != string::npos)
    {
        domain = delim(url,"/",1);   
        return domain;  
    }
    domain = delim(url,"/",0);
    return domain;
}

/*比较一级域名是否相等*/
inline bool IsSameDomainUrl(std::string a, std::string b){
    
    std::string a_domain = GetUrlDomain(a);
    std::string b_domain = GetUrlDomain(b);
    int n = a.find(".",0);

    a_domain = a_domain.substr(n+1,a_domain.length());
    b_domain = b_domain.substr(n+1,b_domain.length());

    if(a_domain == b_domain)    return true;
    return false;
}


// inline std::string JoinUrl(std::string domain, std::string path){
//     //拼接url
//     std::string complete_url;
//     complete_url = domain + "/" + path;
//     return complete_url;
// }

inline std::string StdUrl(std::string url){
    //标准化url
    std::string std_url;
    if(url.find("http://") != string::npos)        //匹配到http://
        return url;
    else
        std_url = "http://" + url;
    return std_url;
}

inline bool IsBeginWith(std::string s, std::string m) {
    if (m.length() > s.length()) {
        return false;
    }
    for (int i = 0; i < m.length(); i++) {
        if (m[i] != s[i]) {
            return false;
        }
    }
    return true;
}

inline bool IsEndWith(std::string s, std::string m) {
    if (m.length() > s.length()) {
        return false;
    }
    for (int i = 0; i < m.length(); i++) {
        if (m[i] != s[s.length() - m.length() + i]) {
            return false;
        }
    }
    return true;
}


inline std::pair<std::string, std::string> ParseMeta(std::string text) {
    // 用于把meta标签解析成k-v pair
    enum class MetaStatus {
        NONE,
        NAME,
        CONTENT,
    };

    MetaStatus status = MetaStatus::NONE;
    std::string token;
    std::string name;
    std::string content;

    for (auto i : text) {
        token.push_back(i);
        if (status == MetaStatus::NONE && (token == "name=\"" || token == "http-equiv=\"")) {
            // NONE + name
            status = MetaStatus::NAME;
        } else if (status == MetaStatus::NONE && token == "content=\"") {
            // NONE + content
            status = MetaStatus::CONTENT;
        } else if (status == MetaStatus::NONE && token == "charset=\"") {
            name = "charset";
            status = MetaStatus::CONTENT;
        } else if ((status == MetaStatus::NAME || status == MetaStatus::CONTENT) && i == '"') {
            status = MetaStatus::NONE;
            token.clear();
        } else if (status == MetaStatus::NAME) {
            name.push_back(i);
        } else if (status == MetaStatus::CONTENT) {
            content.push_back(i);
        } else if (status == MetaStatus::NONE && i == ' ') {
            token.clear();
        }
    }

    return std::pair<std::string, std::string>(name, content);
}

inline std::string List2String(std::list<char> s) {
    std::string res;
    for (auto i : s) {
        res.push_back(i);
    }
    return res;
}

inline std::list<char> String2List(std::string s) {
    std::list<char> res;
    for (auto i : s) {
        res.push_back(i);
    }
    return res;
}
inline  std::string DropTag(std::string s){
    auto l = String2List(s);
    std::vector<std::list<char>::iterator> sure_delete_stack;
    enum DropTagStatus {
        NONE,
        TAG
    };

    DropTagStatus status = DropTagStatus::NONE;
    for (auto it = l.begin(); it != l.end(); it++){
        char item = *it;
        if (item == '<'){
            status = DropTagStatus::TAG;
        }
        if (status == DropTagStatus::TAG){
            sure_delete_stack.push_back(it);
        }
        if (item == '>'){
            status = DropTagStatus::NONE;
        }
        if (status == DropTagStatus::NONE && (item ==' ') ){
            sure_delete_stack.push_back(it);
        }
    }
    while (!sure_delete_stack.empty()) {
        auto i = sure_delete_stack.back();
        l.erase(i);
        sure_delete_stack.pop_back();
    }
    return List2String(l);
}
inline std::string GetHost(std::string url) {
    size_t pos = url.find("://");
    if (pos != url.npos)
        url = url.substr(pos + 3);
    pos = url.find("/");
    if (pos == url.npos) {

    } else
        url = url.substr(0, pos);
    return url;
}

inline std::pair<int, int> FindMaxTag2WordPos(const std::string &text, int start_pos, int end_pos) {
    bool tag_flag = false;
    int offset = 0;

    int len = end_pos - start_pos + 500;

    auto *tag_sum = new int[len];
    for (int i = 0; i < len; i++) {
        tag_sum[i] = 0;
    }
    auto *word_sum = new int[len];
    for (int i = 0; i < len; i++) {
        word_sum[i] = 0;
    }

    for (int it = start_pos; it != end_pos; it++) {

        offset = it - start_pos;
        char item = text[it];
        if (item == '<') {
            tag_flag = true;
        } else if (item == '>') {
            tag_flag = false;
        }
        if (offset == 0) {
            tag_sum[offset] = tag_flag ? 1 : 0;
            word_sum[(end_pos - start_pos) - offset] = tag_flag ? 0 : 1;
        } else {
            tag_sum[offset] = tag_sum[offset - 1] + tag_flag ? 1 : 0;
            word_sum[(end_pos - start_pos) - offset] = word_sum[(end_pos - start_pos) - offset - 1] + tag_flag ? 0 : 1;
        }
    }

    int top_offset = 0;
    int top_value = tag_sum[0] + word_sum[0];
    for (int i = 1; i < offset - 1; i++) {
        int v = tag_sum[i] + word_sum[i];
        if (v > top_value) {
            top_offset = i;
            top_value = v;
        }
    }

    return std::pair<int, int>(top_offset + start_pos, top_value);
}


inline std::pair<int, int> FindMaxWord2TagPos(const std::string &text, int start_pos, int end_pos) {
    bool tag_flag = false;
    int offset = 0;

    int len = end_pos - start_pos + 500;

    auto *tag_sum = new int[len];
    for (int i = 0; i < len; i++) {
        tag_sum[i] = 0;
    }
    auto *word_sum = new int[len];
    for (int i = 0; i < len; i++) {
        word_sum[i] = 0;
    }

    for (int it = start_pos; it != end_pos; it++) {

        offset = it - start_pos;
        char item = text[it];
        if (item == '<') {
            tag_flag = true;
        } else if (item == '>') {
            tag_flag = false;
        }
        if (offset == 0) {
            word_sum[offset] = tag_flag ? 1 : 0;
            tag_sum[(end_pos - start_pos) - offset] = tag_flag ? 0 : 1;
        } else {
            word_sum[offset] = word_sum[offset - 1] + tag_flag ? 1 : 0;
            tag_sum[(end_pos - start_pos) - offset] = tag_sum[(end_pos - start_pos) - offset - 1] + tag_flag ? 0 : 1;
        }
    }

    int top_offset = 0;
    int top_value = tag_sum[0] + word_sum[0];
    for (int i = 1; i < offset - 1; i++) {
        int v = tag_sum[i] + word_sum[i];
        if (v > top_value) {
            top_offset = i;
            top_value = v;
        }
    }

    return std::pair<int, int>(top_offset + start_pos, top_value);
}


inline std::string GetPath(std::string url) {
    size_t pos = url.find("://");
    if (pos != url.npos) url = url.substr(pos + 3);
    pos = url.find('/');
    if (pos == url.npos)
        url = "/";
    else
        url = url.substr(pos);
    return url;
}

inline bool isLegal(char s){
    if (s == ':' || s=='\r'|| s=='\n'){
        return false;
    }
    return true;
};


inline std::map<std::string, std::string> ParseHttpHeader(std::string raw) {
    enum class ParseMetaStatus {
        NONE,
        KEY,
        VALUE,
        BETWEEN
    };
    std::string tmp_key;
    std::string tmp_value;

    ParseMetaStatus status = ParseMetaStatus::NONE;

    auto m = std::map<std::string, std::string>();

    for (auto i : raw) {
        if (status == ParseMetaStatus::NONE && isalpha(i)) {
            status = ParseMetaStatus::KEY;
            tmp_key.push_back(i);
        } else if (status == ParseMetaStatus::KEY && i == ':') {
            status = ParseMetaStatus::BETWEEN;
        } else if (status == ParseMetaStatus::KEY) {
            tmp_key.push_back(i);
        } else if (status == ParseMetaStatus::BETWEEN && isLegal(i)) {
            status = ParseMetaStatus::VALUE;
            tmp_value.push_back(i);
        } else if (status == ParseMetaStatus::VALUE && i == '\r') {
            status = ParseMetaStatus::NONE;
            m.insert(std::pair<std::string, std::string >(tmp_key, tmp_value));
            tmp_key.clear();
            tmp_value.clear();
        }
        else if (status == ParseMetaStatus::VALUE) {
            tmp_value.push_back(i);
        }
    }
    return m;
}

inline std::string HttpHeader2String(std::map<std::string, std::string> header) {
   std::string res;
    for (auto i: header){
        res = res+i.first + ": "+i.second + "\r\n";
    }
    return res;
}

inline int ParseResponseMeta(const std::string &text) {
    auto res = text.substr(9, 3);
    int code = -1;
    std::stringstream ss;
    ss << res;
    ss >> code;
    return code;
}

inline std::map<std::string, std::string> ParseUrl(std::string url) {
    std::map<std::string, std::string> mapUrl;
    int pos = url.find("://");
    std::string protocol;
    if (pos != url.npos)
        protocol = url.substr(0, pos);
    mapUrl.insert(std::pair<std::string, std::string>("protocol", protocol));
    url = url.substr(pos + 3);
    std::string domain;
    pos = url.find("/");
    domain = url.substr(0, pos);
    mapUrl.insert(std::pair<std::string, std::string>("domain", domain));
    url = url.substr(pos + 1);
    mapUrl.insert(std::pair<std::string, std::string>("path", url));
    /*std::map<std::string, std::string>::iterator it;
        for(it = mapUrl.begin(); it != mapUrl.end(); it++)
                cout << it->first << " " << it->second << endl;*/
    return mapUrl;
}