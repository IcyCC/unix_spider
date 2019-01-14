//
// Created by 苏畅 on 2019/1/14.
//

#include "util.h"

inline std::string delim(std::string str, std::string delim, int pos)//分割源字符、分割字符、返回容器元素位置
{
    std::vector<std::string> res;
    char *strs = new char[str.length() + 1];
    strcpy(strs, str.c_str());

    char *d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while (p) {
        std::string s = p;
        res.push_back(s);
        p = strtok(NULL, d);
    }

    delete[] strs;
    delete[] d;
    return res[pos];
}


inline bool IsAbsUrl(std::string url) {
    //根据URL的构成，由两部分构成：<Schema>:<特定于本schema的子串> 因此,只要直接判有没有字符 ":" 就行。有：是绝对，没有相对。
    if (url.find(":") != std::string::npos)
        return true;
    if (url[0] != '.' && url[0] != '/')     //url第一个字符不为“.”或"/"时，为绝对路径
        return true;
    return false;
}

inline int GetUrlLevel(std::string url) {
    std::vector<std::string> delim_url;
    std::string temp;
    std::istringstream is(url);
    //将url分割放入容器，读取容器大小，即为level
    while (std::getline(is, temp, '/')) {
        delim_url.push_back(temp);
    }
    if (url.find("//") != std::string::npos)
        return delim_url.size() - 1;
    return delim_url.size();
}

/*返回一个二级域名*/
inline std::string GetUrlDomain(std::string url) {
    std::string domain;

    if (url.find("http://") != std::string::npos) {
        domain = delim(url, "/", 1);
        return domain;
    }
    domain = delim(url, "/", 0);
    return domain;
}

/*比较一级域名是否相等*/
inline bool IsSameDomainUrl(std::string a, std::string b) {

    std::string a_domain = GetUrlDomain(a);
    std::string b_domain = GetUrlDomain(b);

//    auto a_level_domain = SpliteString(a_domain,);
    if (a_domain == b_domain) return true;
    return false;
}


inline std::string JoinUrl(std::string domain, std::string path) {
    //拼接url
    std::string complete_url;
    complete_url = domain + "/" + path;
    return complete_url;
}

inline std::string StdUrl(std::string url) {
    //标准化url
    std::string std_url;
    if (url.find("http://") != std::string::npos)        //匹配到http://
        return url;
    else
        std_url = "http://" + url;
    return std_url;
}
