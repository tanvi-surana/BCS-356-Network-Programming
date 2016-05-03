#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 9002
#define SERV_IP "127.0.0.1"
#define MAX 1001

int main()
{
	int listenfd,connfd;
	struct sockaddr_in server,client;
	socklen_t clilen;
	char buff[MAX];
	int n;

    listenfd=socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr(SERV_IP);
    server.sin_port=htons(PORT);

    bind(listenfd,(struct sockaddr*)&server,sizeof(server));

    listen(listenfd,5);

    for(;;)
    {   
    	clilen=sizeof(client);
    	connfd=accept(listenfd,(struct sockaddr*)&client,&clilen);
    	while((n=read(connfd,buff,MAX))>0)
        {
        	printf("Echoing back\n");
        	write(connfd,buff,n);
        }
        if(n==0)
          close(connfd);		
    }
    close(listenfd);

    return 0;
}