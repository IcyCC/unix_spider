//
// Created by 苏畅 on 2019/1/14.
//

#include<vector>
#include<string>
#include"request.h"
#include"response.h"
#include"data.h"
#include"work_list.h"
#include"parser.h"
#include "url.h"

using namespace std;
auto work_list = usp::WorkList();


int main() {

    work_list.Put("http://www.gmw.cn/");
    while (!work_list.IsEmpty()) {

        auto url = work_list.Get();

        auto req = usp::Request(url);
        auto resp = req.Fetch();
        if (resp.status != 200) {
            cout << "ERROR" << "  URL: " << url << "失败  状态码 :" << resp.status << endl;
            if (resp.status > 300 && resp.status <310){
               auto redir_url = resp.ReadHeader("Locatioin");
               redir_url = StdUrl(redir_url);
               if(!IsSameDomainUrl(url, redir_url)){
                   work_list.Put(redir_url);
               }
            }
            continue;
        }
        auto par = usp::Parser(resp.body);
        par.ParseHeader();

        auto author = par.ReadMeta("author");
        if (author != usp::SPECIAL_NONE) {
            // 有作者详情页
            par.ParseMainBody();
            auto data = usp::Data();
            data.body = par.body;
            data.title = par.title;
            data.author = author;
            data.domain = GetUrlDomain(url);
            data.coding = ReadCoderByHeader(par.header);
            cout << "INFO: " << "爬取到内容页  URL: " << url << endl;
            data.Dumps("./data/" + data.domain + "/" +data.title+".txt");
        }
        auto new_urls = par.GetAllUrls();
        for (auto n_url : new_urls) {
            string std_n_url;
            if (IsAbsUrl(n_url)) {
                // 绝对
                std_n_url = StdUrl(n_url);

            if (IsSameDomainUrl(url, std_n_url)) {
                work_list.Put(std_n_url);
            }
            }
        }

    }
}