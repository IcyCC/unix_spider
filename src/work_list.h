#include<string>

namespace usp{
    class WorkList {
        public:
            bool put(std::string v);
            std::string get();
            bool is_empty();
    };
}
