#include<vector>
#include<string>
#include <pthread.h>
#include <semaphore.h>
#include"request.h"
#include"response.h"
#include"data.h"
#include"work_list.h"
#include"parser.h"
#include "url.h"
#include "buffer.h"
using namespace std;
auto work_list = usp::WorkList();
pthread_mutex_t work_lis_mutex;

void *consume(void *args) {
    while (true) {
        buffer_item item;
        RemoveItem(&item);
        pthread_mutex_lock(&work_lis_mutex);
        auto url = work_list.Get();
        pthread_mutex_unlock(&work_lis_mutex);
        if (url == "EXIT") {
            return NULL;
        }
        auto req = usp::Request(url);
        auto resp = req.Fetch();
        if (resp.status != 200) {
            cout << "ERROR" << "  URL: " << url << "失败  状态码 :" << resp.status << endl;
        }
        auto par = usp::Parser(resp.body);
        par.ParseHeader();

        auto author = par.ReadMeta("author");
        if (author != par.SPECIAL_NONE) {
            // 有作者详情页
            par.ParseMainBody();
            auto data = usp::Data();
            data.body = par.body;
            data.title = par.title;
            data.author = author;
            cout << "INFO: " << "爬取到内容页  URL: " << url << endl;
            data.Dumps("/Users/suchang/Code/unix_lab/unxi_spider/data/" + url);
        }
        auto new_urls = par.GetAllUrls();
        pthread_mutex_lock(&work_lis_mutex);
        for (auto n_url : new_urls) {
            string std_n_url;
            if (IsAbsUrl(n_url)) {
                // 绝对
                std_n_url = StdUrl(n_url);
            } else {
                auto abs_url = JoinUrl(url, n_url);
                std_n_url = StdUrl(abs_url);
            }
            if (IsSameDomainUrl(url, std_n_url)) {
                work_list.Put(std_n_url);
                InsertItem(1);
            }
        }
        pthread_mutex_unlock(&work_lis_mutex);

    }
}


int main() {
    const int P_NUM = 10;
    Initialize();
    pthread_mutex_init(&work_lis_mutex, NULL);

    work_list.Put("http://www.gmw.cn/");
    pthread_t p_ids[P_NUM];
    for (int i = 0; i < P_NUM; i++) {
        pthread_create(&p_ids[i], NULL, consume, NULL);
    }
    InsertItem(1);
    for (int i = 0; i < P_NUM; i++) {
        pthread_join(p_ids[i], NULL);
    }

}