#include "parser.h"

#include <string>

usp::Parser::Parser(std::string raw) {
    raw_text = new BoolString(raw);
}


std::string usp::Parser::GetMainBody() {
    return body;
}

bool usp::Parser::ParseMainBody() {
    raw_text->ForEach([this](int index, char item, BoolString * bs) {
        
    });
    return false;
}

void usp::BoolString::ForEach(std::function<void (int, char, BoolString*bs)> f) {
    for(int i = 0; i<str.length(); i++){
        if (pBoolean[i]){
            f(i, str[i], this);
        }
    }
}
