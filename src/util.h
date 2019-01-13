//
// Created by 苏畅 on 2019/1/7.
// 常用的工具函数
//
#pragma once

#include <string>
#include <map>
#include <list>
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


inline std::string GetUrlDomain(std::string url ){
    // 获取url的主机
    std::string domain;

    int position = url.find("http://");
    //若url前面有http://,则分割后容器中第二个元素位域名，否则，第一个元素为域名
    if(position >= 0)
    {
        domain = delim(url,"/",1);    
        return domain;    
    }
    domain = delim(url,"/",0);
    return domain;
}

inline bool IsSameDomainUrl(std::string a, std::string b){
    
    std::string a_domain = GetUrlDomain(a);
    std::string b_domain = GetUrlDomain(b);
    if(a_domain == b_domain)    return true;
    return false;
}


inline std::string JoinUrl(std::string domain, std::string path){
    //拼接url
    std::string complete_url;
    complete_url = domain + path;
    return complete_url;
}

inline std::string StdUrl(std::string url){
    //标准化url
    std::string std_url;
    int position = url.find("http://");
    if(position >= 0)        //匹配到http://
        return url;
    else
        std_url = "http://" + url;
    return std_url;
}



inline bool IsBeginWith(std::string s, std::string m){
    if (m.length() > s.length()){
        return false;
    }
    for (int i =0 ; i<m.length(); i++){
        if(m[i] != s[i]){
            return false;
        }
    }
    return true;
}

inline bool IsEndWith(std::string s, std::string m){
    if (m.length() > s.length()){
        return false;
    }
    for (int i =0 ; i<m.length(); i++){
        if (m[i]!=s[s.length()- m.length() + i]){
            return false;
        }
    }
    return true;
}


inline std::pair<std::string, std::string> ParseMeta(std::string text){
    // 用于把meta标签解析成k-v pair
    enum class MetaStatus{
        NONE,
        NAME,
        CONTENT,
    };

    MetaStatus status = MetaStatus::NONE;
    std::string token;
    std::string name;
    std::string content;

    for (auto i : text){
        token.push_back(i);
        if (status == MetaStatus::NONE&&(token == "name=\"" || token == "http-equiv=\"")){
            // NONE + name
            status = MetaStatus::NAME;
        } else if (status == MetaStatus::NONE && token =="content=\""){
            // NONE + content
            status = MetaStatus::CONTENT;
        } else if (status == MetaStatus::NONE && token == "charset=\"") {
            name = "charset";
            status = MetaStatus::CONTENT;
        }else if ((status == MetaStatus::NAME || status == MetaStatus::CONTENT) && i == '"'){
            status = MetaStatus::NONE;
            token.clear();
        }else if (status == MetaStatus::NAME){
            name.push_back(i);
        } else if (status == MetaStatus::CONTENT){
            content.push_back(i);
        }  else if (status ==MetaStatus::NONE && i == ' '){
            token.clear();
        }
    }

    return std::pair<std::string, std::string>(name, content);
}

inline std::string List2String(std::list<char> s){
    std::string res;
    for(auto i : s){
        res.push_back(i);
    }
    return res;
}

inline std::list<char> String2List(std::string s){
    std::list<char> res;
    for(auto i : s){
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
    }
    while (!sure_delete_stack.empty()) {
        auto i = sure_delete_stack.back();
        l.erase(i);
        sure_delete_stack.pop_back();
    }
    return List2String(l);
}


