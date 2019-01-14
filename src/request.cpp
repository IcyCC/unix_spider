#include "request.h"

bool usp::Request::SetHeader(std::map<std::string, std::string> h) {
    header = HttpHeader2String(h);
    header_map = h;
    return true;
}


usp::Response usp::Request::Fetch() {

    std::cout<< "INFO: 发送请求  URL: "<< url<<std::endl;
    int isock;
    struct sockaddr_in pin;
    struct hostent *remoteHost;
    std::string message;
    std::string host = GetHost(url);//将url提取出域名
    //判断能否解析主机，可能会出现的问题是某些Linux主机无法解析外网主机，需要设置、dns，如果仅仅是测试，可以采用本地IP作为host
    remoteHost = gethostbyname(host.c_str());
    if (remoteHost == 0) {
        printf("Error resolving host\n");
        exit(1);
    }
    bzero(&pin, sizeof(pin));
    pin.sin_family = AF_INET;
    pin.sin_port = htons(80);
    pin.sin_addr.s_addr = ((struct in_addr *) (remoteHost->h_addr))->s_addr;

    //打开socket
    if ((isock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Error opening socket!\n");
        exit(1);
    }
    std::string path = GetPath(url);
    std::string header_0;
    header_0 = "Host: " + host + "\r\n";
    //采用get方式获取数据，没有传递参数情况下采用这种方式
    message = message +method + " " +path + " HTTP/1.1\r\n" + header_0
            + header + "\r\n\r\n";

    if (connect(isock, (struct sockaddr *) &pin, sizeof(pin)) == -1) {
        printf("Error connecting to socket\n");
        exit(1);
    }

    if (send(isock, message.c_str(), strlen(message.c_str()), 0) == -1) {
        printf("Error in send\n");
        exit(1);
    }

    std::string res;
    char buffer[4096];
    while (recv(isock, buffer, 4096, 0) > 0) {
        res += buffer;
        memset(buffer, 0, sizeof(buffer));
    }
    std::cout<< "INFO: 收到响应  URL: "<< url<<std::endl;
    close(isock);
    return Response(res);

}