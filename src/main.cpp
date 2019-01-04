#include<vector>
#include<string>
#include"request.h"
#include"response.h"
#include"data.h"
#include"work_list.h"
#include"parser.h"
#include"url.h"

using namespace std;

int main(){
    usp::WorkList url_sets;
    url_sets.put("出事链接");
    
    while(true){
        if (url_sets.is_empty()){
            break;
        }

        auto url = url_sets.get();

        auto req = usp::Request();
        auto resp = req.fetch();

        auto p = usp::Paser(resp.RawBody());

        auto data = usp::Data();
        data.body = p.GetMainBody();
        data.dumps("路径");
        
        auto sp_urls = p.GetAllUrls();

        for (auto sp_url : sp_urls){
            auto sp_url_obj = usp::Url(sp_url);
            //条件判断 放入 url_sets
        }
    }
}