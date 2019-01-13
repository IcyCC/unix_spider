#include "request.h"
bool usp::Request::SetHeader(std::string header)
{
	if(header == NULL)
        return 0;
    header=header;
    return 1;
}

usp::Response Request:: Fetch()
{
	char message[512];
	memset(message,sizeof(message),0); 
	sprintf(message, "Host:"); 
	strcat(message,host.c_str());
	strcat(message,"\r\n");*/
	strcat(message, "Accept: */*\r\n");  
	strcat(message, "User-Agent: Mozilla/4.0(compatible)\r\n");  
	strcat(message, "connection:Keep-Alive\r\n");  
	strcat(message, "\r\n\r\n"); 
	std::string header;
	header=message; 
	Request::Setheader(header);
	char buffer[512];  
	int isock;  
	struct sockaddr_in pin;  
	struct hostent * remoteHost;  
	char message[512];  
	int done = 0;  
	int chars = 0;  
	int l = 0;  
	string host=gethost(url);
	//判断能否解析主机，可能会出现的问题是某些Linux主机无法解析外网主机，需要设置、dns，如果仅仅是测试，可以采用本地IP作为host  
	if( (remoteHost = gethostbyname(host.c_str()) == 0 )  
	{  
	printf("Error resolving host\n");  
	exit(1);  
	}  
	  
	bzero(message,sizeof(message));  
	bzero(&pin,sizeof(pin));  
	pin.sin_family = AF_INET;  
	pin.sin_port = htons(port);  
	pin.sin_addr.s_addr = ( (struct in_addr *)(remoteHost->h_addr) )->s_addr;  
	  
	//打开socket  
	if( (isock = socket(AF_INET, SOCK_STREAM, 0)) == -1)  
	{  
	printf("Error opening socket!\n");  
	exit(1);  
	}    
	
	
  
}