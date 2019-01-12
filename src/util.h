//
// Created by 苏畅 on 2019/1/7.
// 常用的工具函数
//

#pragma once

#include <string>
#include <map>

bool IsSameDomainUrl(std::string a, std::string b){
    return false;
}


bool IsBeginWith(std::string s, std::string m){
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

bool IsEndWith(std::string s, std::string m){
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


std::pair<std::string, std::string> ParseMeta(std::string text){
    // 用于把meta标签解析成k-v pair
    enum class MetaStatus{
        NONE,
        NAME,
        NAME_V,
        CONTENT,
        CONTENT_V,
    };

    MetaStatus status = MetaStatus::NONE;
    std::string token;
    std::string name;
    std::string content;

    for (auto i : text){
        if(i == ' '){
            // 清空token
            token.clear();
        } else {
            token.push_back(i);
        }

        if (status == MetaStatus::NONE&&(token == "name" || token == "http-equiv")){
            // NONE + name
            status = MetaStatus::NAME;
        } else if (status == MetaStatus::NONE && token =="content"){
            // NONE + content
            status = MetaStatus::CONTENT;
        } else if (status == MetaStatus::NAME && i == '"'){
            // NAME  " 内容开始
            status = MetaStatus::NAME_V;
        } else if (status == MetaStatus::CONTENT && i == '"'){
            // CONTENT  " 内容开始
            status = MetaStatus::CONTENT_V;
        } else if (status == MetaStatus::NAME_V && i != '"'){
            name.push_back(i);
        } else if (status == MetaStatus::CONTENT_V && i != '"'){
            content.push_back(i);
        } else if ((status == MetaStatus::NAME_V || status == MetaStatus::CONTENT_V) && i == '"'){
            status = MetaStatus::NONE;
            token.clear();
        }
    }

    return std::pair<std::string, std::string>(name, content);
}