#include "request.h"
std::string usp::Reponse GetRaw()
{
	return raw;
}
std::string usp::Reponse RawHeader()
{
	int pos=raw.find("\n"); 
	if(pos!=raw.npos)raw=raw.substr(pos);
	return raw;
	
}
std::string usp::Response:: ReadHeader(std::string key)
{
	if(header.count(key)>0)
 	{
 		std::string value;
		std::map<std::string, std::string>::iterator  iter;
		iter = header.find(key);
		if(iter != header.end())
		{
	       value=iter->second;
	       return value;
		}
		else
		{
	      return null;
		}
     		
 	}
 	else
 		return null;
	
}

bool usp::Request::SetHeader(std::string header)
{
	if(header == NULL)
        return 0;
    header=header;
    return 1;
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
	std::string host=Gethost(url);//将url提取出域名 
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
	std::string path=Getpath(url);  
	std::string header_0;
	header_0="Host:"+host.c_str();+"\r\n"+"Accept: */*\r\n"+"User-Agent: Mozilla/4.0(compatible)\r\n"+"connection:Keep-Alive\r\n"+ "connection:Keep-Alive\r\n"+"\r\n\r\n";
	Setheader(header_0);
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
	char receive[512]=""; 
	int i=0;
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
		receive[i]=*buffer;
		i++;
		
	}
	response.raw=receive;//获取响应头
	std::string rec=receive; 
	std::map<std::string, std::string> header;
	header=ParseHttpHeader(rec);
	Response.header=header;//map
	int pos=rec.find("\n");
	if(pos!=rec.npos) rec=rec.substr(0,pos);
	pos=rec.find("HTTP/1.1");
	rec=rec.substr(pos+8);
	int pos2=rec.find("OK");
	rec=rec.substr(0,pos2);
	rec.erase(0,rec.find_first_not_of(" "));
	rec.erase(rec.find_last_not_of(" ") + 1);
	cout<<rec<<endl;
	int status;
	stringstream ss;
	ss<<rec;
	ss>>status;
	cout<<status<<endl;
	response.status=status;//获取状态码 
	
	
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

  
	
  

