#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<error.h>
#include<netinet/in.h>


#define SERV_PORT 9002
#define SERV_IP "127.0.0.1"
#define MAXLINE 1001
#define MAX 1001
 
int main()
{
	struct sockaddr_in server,client;
	socklen_t clilen;
	int listenfd,sockfd,n;
    char buff[MAXLINE];

	listenfd=socket(AF_INET,SOCK_DGRAM,0);

	bzero(&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(SERV_IP);
	server.sin_port=htons(SERV_PORT);

	if((bind(listenfd,(struct sockaddr*)&server,sizeof(server)))<0)
     {
     	perror("Bind failed");
     }
     else
     {
     	printf("Bind successful \n");
     } 
    
    clilen=sizeof(client);
    
  
   for(;;)
   {
      //printf("Entering loop");
      clilen=sizeof(client);
      n=recvfrom(listenfd,buff,MAXLINE,0,(struct sockaddr*)&client,&clilen);
      sendto(listenfd,buff,n,0,(struct sockaddr*)&client,clilen);
      buff[n]=0;
      printf("Recd %s from client\n",buff);

    }


}