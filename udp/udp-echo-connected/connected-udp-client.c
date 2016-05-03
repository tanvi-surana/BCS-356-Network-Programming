#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>

#define SERV_PORT 9002
#define SERV_IP "127.0.0.1"
#define MAX 1001


void dg_cli(int sockfd,struct sockaddr* server,socklen_t serv_len)
{

	int n;
	char sendline[MAX],recvline[MAX+1];
	connect(sockfd,server,serv_len);
	while(fgets(sendline,MAX,stdin)!=NULL)
    {
    	write(sockfd,sendline,strlen(sendline));
    	n=read(sockfd,recvline,MAX);
    	recvline[n]=0;
    	fputs(recvline,stdout);
    	bzero(recvline,sizeof(recvline));
	    bzero(sendline,sizeof(sendline));
    }		
}

 
int main()
{
	int connfd,listenfd;
	struct sockaddr_in server,client;
	socklen_t len;

	listenfd=socket(AF_INET,SOCK_DGRAM,0);
    
    bzero(&server,sizeof(server));

    server.sin_family=AF_INET;
    server.sin_port=htons(SERV_PORT);
    server.sin_addr.s_addr=inet_addr(SERV_IP);
    
    len=sizeof(server);

     dg_cli(listenfd,(struct sockaddr*)&server,len);
    

   return 0;
}