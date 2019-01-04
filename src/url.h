#include<string>
#include<vector>

namespace usp{
    class Url {
        public:
            std::string host;
            std::vector<std::string> domains;
            std::string raw_body;
        public:
            Url(std::string url);

    };
}
