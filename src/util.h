//
// Created by 苏畅 on 2019/1/7.
// 常用的工具函数
//

#pragma once

#include <string>

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
