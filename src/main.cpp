#include<vector>
#include<string>
#include"request.h"
#include"response.h"
#include"data.h"
#include"work_list.h"
#include"parser.h"

using namespace std;

int main(){
    usp::WorkList url_sets;
    url_sets.Put("出事链接");
    
    while(true){
        if (url_sets.IsEmpty()){
            break;
        }

        auto url = url_sets.Get();

        auto req = usp::Request();
        auto resp = req.Fetch();

        auto p = usp::Parser(resp.RawBody());

        auto data = usp::Data();
        data.body = p.GetMainBody();
        data.Dumps("路径");
        
        auto sp_urls = p.GetAllUrls();

        for (auto sp_url : sp_urls){
            //条件判断 放入 url_sets
        }
    }
}