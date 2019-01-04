#include<string>

namespace usp{
    class Request {
        private: 
            std::string url;
            std::string method;
            std::string header;
        public:
            std::string fetch(); //爬取
            bool SetHeader(std::string header);//设置http的header的文本
    };
}
