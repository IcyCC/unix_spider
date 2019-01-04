#include<string>

namespace usp{
    class Data {
        public:
            std::string body; //正文    

            bool loads(std::string path); //从文件加载
            bool load(std::string ); //从字符串加载
            std::string dump(); //生成字符串
            bool dumps (std::string path);// 写入到文件
            };
}
