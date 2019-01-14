#include<vector>
#include<string>
#include"request.h"
#include"response.h"
#include"data.h"
#include"work_list.h"
#include"parser.h"
#include "url.h"

using namespace std;

int main(){

    auto work_list = usp::WorkList();
    work_list.Put("http://www.gmw.cn/");

    while(!work_list.IsEmpty()){
        auto url = work_list.Get();
        auto req = usp::Request(url);
        auto resp = req.Fetch();
        if (resp.status != 200){
            cout<<"ERROR"<<"  URL: "<<url<<"失败  状态码 :"<<resp.status<<endl;
        }
        auto par = usp::Parser(resp.body);
        par.ParseHeader();

        auto author = par.ReadMeta("author");
        if (author != par.SPECIAL_NONE){
            // 有作者详情页
            par.ParseMainBody();
            auto data = usp::Data();
            data.body = par.body;
            data.title = par.title;
            data.author = author;
            cout<<"INFO: "<<"爬取到内容页  URL: "<<url<<endl;
            data.Dumps("/Users/suchang/Code/unix_lab/unxi_spider/data/"+url);
        }
        auto new_urls = par.GetAllUrls();
        for (auto n_url : new_urls){
            string std_n_url;
            if (IsAbsUrl(n_url)){
                // 绝对
                std_n_url = StdUrl(n_url);
            } else {
                auto abs_url = JoinUrl(url, n_url);
                std_n_url = StdUrl(abs_url);
            }
            if (IsSameDomainUrl(url, std_n_url)){
                work_list.Put(std_n_url);
            }
        }
    }
}