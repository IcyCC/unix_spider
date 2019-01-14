#include "request.h"

bool usp::Request::SetHeader(std::map<std::string, std::string> h) {
    header = HttpHeader2String(h);
    header_map = h;
    return true;
}


usp::Response usp::Request::Fetch() {


    int isock;
    struct sockaddr_in pin;
    struct hostent *remoteHost;
    std::string message;
    std::string host = GetHost(url);//?url?????
    //????????????????????Linux????????????????dns???????????????IP??host
    remoteHost = gethostbyname(host.c_str());
    if (remoteHost == 0) {
        printf("Error resolving host\n");
        exit(1);
    }
    bzero(&pin, sizeof(pin));
    pin.sin_family = AF_INET;
    pin.sin_port = htons(80);
    pin.sin_addr.s_addr = ((struct in_addr *) (remoteHost->h_addr))->s_addr;

    //??socket
    if ((isock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Error opening socket!\n");
        exit(1);
    }
    std::string path = GetPath(url);
    std::string header_0;
    header_0 = "Host:" + host + "\r\n";
    //??get??????????????????????
    message = message +method + " " +path + " HTTP/1.1\r\n" + header_0
            + header + "\r\n\r\n";

    std::cout<< message<<std::endl;
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

    close(isock);
    return Response(res);

}