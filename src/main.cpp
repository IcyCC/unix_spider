#include<vector>
#include<string>
#include"request.h"
#include"response.h"
#include"data.h"
#include"work_list.h"
#include"parser.h"

using namespace std;

int main(){
    string url = "http://www.gmw.cn/";
    auto req = usp::Request(url);
    auto resp = req.Fetch();
    cout<<resp.body;
}