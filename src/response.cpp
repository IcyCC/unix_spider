//
// Created by 苏畅 on 2019/1/14.
//
#include "request.h"

std::string usp::Response::GetRaw() {
    return raw;
}

std::string usp::Response::GetRawHeader() {
    return raw_header;
}

std::string usp::Response::ReadHeader(std::string key) {
    auto r = header.find(key);
    if (r == header.end()) {
        return "";
    } else {
        return r->second;
    }
    return "";
}
