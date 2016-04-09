#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>

#define MAXLINE 1001
#define SERV_IP "127.0.0.1"
#define SERV_PORT 9002

void str_echo(int sockfd)
{
	// ssize_t n;
	// char line[MAXLINE];
	// for(;;)
	// {
	// scanf(" %s", line);
	// send(sockfd, line , n, 0);
	// recv(sockfd, line , MAXLINE,0);
	// printf("\n\n from server -- %s", line);
	// }

    char sendline[100];
    char recvline[100];
    while(1)
    {
        bzero( sendline, 100);
        bzero( recvline, 100);
        fgets(sendline,100,stdin); /*stdin = 0 , for standard input */
 
        write(sockfd,sendline,strlen(sendline)+1);
        read(sockfd,recvline,100);
        printf("%s",recvline);
    }
 

}

int main(){
	int sockfd;

	struct sockaddr_in server;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&server,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr(SERV_IP);
    server.sin_port=htons(SERV_PORT);

    connect(sockfd,(struct sockaddr*)&server,sizeof(server));
    str_echo(sockfd); 

}