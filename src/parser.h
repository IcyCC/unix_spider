#include<string>

namespace usp{
    class Parser {
        public:
            std::string body; //正文    

            Parser(std::string raw); // 构造

            std::string GetMainBody(); // 获取正文
            std::string GetAuthor(); // 获取作者
            std::string CommFind(std::string s); //通用查找
            std::vector<string> GetAllUrls();
    };
}
