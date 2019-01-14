#include "request.h"

bool usp::Request::SetHeader(std::string header)
{
	if(header == NULL)
        return 0;
    header=header;
    return 1;
}

string httpsend(string header)
{
	
 header="Host:"+gethost 


  
printf("%s",message);  
}
usp::Response usp::Request:: Fetch()
{
	
	
	char buffer[512];  
	int isock;  
	struct sockaddr_in pin;  
	struct hostent * remoteHost;  
	char message[512];  
	int done = 0;  
	int chars = 0;  
	int l = 0;  
	string host=Gethost(url);//将url提取出域名 
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
	string path=Getpath(url);  
	string header;
//采用get方式获取数据，没有传递参数情况下采用这种方式  
	sprintf(message, method.c_str());  
	strcat(message,path.c_str());
	strcat(message," HTTP/1.1\r\n");
    strcat(message,header.c_str());
	
	
  
	printf("%s",message);  
  
	if( connect(isock, (struct sockaddr *)&pin, sizeof(pin)) == -1 )  
	{  
		printf("Error connecting to socket\n");  
		exit(1);  
	}  
	  
	if( send(isock, message, strlen(message), 0) == -1)  
	{  
		printf("Error in send\n");  
		exit(1);  
	} 
	Response response;
	while(done == 0)  
	{  
		l = recv(isock, buffer, 1, 0);  
		if( l < 0 )  
		done = 1;  
		switch(*buffer)  
		{  
			case '\r':  
				break;  
			case '\n':  
				if(chars == 0)  
					done = 1;  
					chars = 0;  
				break;  
			default:  
				chars++;  
				break;  
		}  
		printf("%c",*buffer);  
		
		response.header=*buffer;
	}
		do  
		{  
			
			l = recv(isock, buffer, sizeof(buffer) - 1, 0);  
			response.body=buffer;
			//printf("%s\n",buffer);
			if( l < 0 )  
			break;  
			*(buffer + l) = 0; 
			//fprintf(fp,"%s",buffer);
			
		}while( l > 0 );  
		
		close(isock);  
		return response;  
		
	  

  
	
  
}
