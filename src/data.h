#pragma once
#include<string>

namespace usp{
    class Data {
        public:
            std::string body; //正文    

            bool Loads(std::string path); //从文件加载
            bool Load(std::string ); //从字符串加载
            std::string Dump(); //生成字符串
            bool Dumps (std::string path);// 写入到文件
            };
}
