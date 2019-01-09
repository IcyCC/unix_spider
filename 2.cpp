#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <netdb.h>  
  
//主机地址,也可以是IP  
char* host = "www.baidu.com";  
int port = 80;  
  
int main(void)  
{  
char buffer[512];  
int isock;  
struct sockaddr_in pin;  
struct hostent * remoteHost;  
char message[512];  
int done = 0;  
int chars = 0;  
int l = 0;  
//判断能否解析主机，可能会出现的问题是某些Linux主机无法解析外网主机，需要设置、dns，如果仅仅是测试，可以采用本地IP作为host  
if( (remoteHost = gethostbyname(host)) == 0 )  
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
  
//采用get方式获取数据，没有传递参数情况下采用这种方式  
sprintf(message, "GET / HTTP/1.1\r\n");  
  
//如果传递参数，如http://www.baidu.com/s?wd=c，则以下参数  
//sprintf(message, "GET /s?wd=c HTTP/1.1\r\n");  
strcat(message, "Host:www.baidu.com\r\n");  
strcat(message, "Accept: */*\r\n");  
strcat(message, "User-Agent: Mozilla/4.0(compatible)\r\n");  
strcat(message, "connection:Keep-Alive\r\n");  
strcat(message, "\r\n\r\n");  
  
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
//这部分是打印http请求信息  
  
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
}  
  
char str[]="";  
do  
{  
l = recv(isock, buffer, sizeof(buffer) - 1, 0);  
if( l < 0 )  
break;  
*(buffer + l) = 0;  
//两种打印方式  
//fputs(buffer, stdout);  
//printf("%c",*buffer);  
//连接成字符串，便于返回数据  
strcat(str,buffer);  
}while( l > 0 );  
//打印网页数据  
printf("ending---%s",str);  
//关闭socket  
close(isock);  
return 0;  
} 
