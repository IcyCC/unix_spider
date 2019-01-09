#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <netdb.h>  
  
//������ַ,Ҳ������IP  
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
//�ж��ܷ�������������ܻ���ֵ�������ĳЩLinux�����޷�����������������Ҫ���á�dns����������ǲ��ԣ����Բ��ñ���IP��Ϊhost  
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
  
//��socket  
if( (isock = socket(AF_INET, SOCK_STREAM, 0)) == -1)  
{  
printf("Error opening socket!\n");  
exit(1);  
}  
  
//����get��ʽ��ȡ���ݣ�û�д��ݲ�������²������ַ�ʽ  
sprintf(message, "GET / HTTP/1.1\r\n");  
  
//������ݲ�������http://www.baidu.com/s?wd=c�������²���  
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
//�ⲿ���Ǵ�ӡhttp������Ϣ  
  
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
//���ִ�ӡ��ʽ  
//fputs(buffer, stdout);  
//printf("%c",*buffer);  
//���ӳ��ַ��������ڷ�������  
strcat(str,buffer);  
}while( l > 0 );  
//��ӡ��ҳ����  
printf("ending---%s",str);  
//�ر�socket  
close(isock);  
return 0;  
} 
