#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 9002
#define MAX 1001

int main()
{
	int sockfd;
	struct sockaddr_in server,client;
	socklen_t clilen;
    char sendline[MAX],recvline[MAX];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	int n;
    
	bzero(&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(SERV_IP);
	server.sin_port=htons(SERV_PORT);

	bind(sockfd,(struct sockaddr*)&server,sizeof(server));

    connect(sockfd,(struct sockaddr*)&server,sizeof(server));
	while(fgets(sendline,MAX,stdin)!=NULL)
	{
	   write(sockfd,sendline,strlen(sendline));
	   n=read(sockfd,recvline,MAX);
	   recvline[n]=0;
	   fputs(recvline,stdout);
	   bzero(&recvline,sizeof(recvline));
	   bzero(&sendline,sizeof(sendline));	
	}
}