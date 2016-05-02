#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>


#define SERV_IP "127.0.0.1"
#define SERV_PORT 9002
#define MAX 1001

void dg_cli(int sockfd,struct sockaddr* server,socklen_t len)
{
	int n;
	char sendline[MAX],recvline[MAX];
	while(fgets(sendline,MAX,stdin)!=NULL)
	{
		sendto(sockfd,sendline,strlen(sendline),0,server,len);
		n=recvfrom(sockfd,recvline,MAX,0,NULL,NULL);
		/*ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);*/

		/* ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen);*/
	    recvline[n]=0;
	    fputs(recvline,stdout);
	    //printf("%s\n",recvline );
	    bzero(recvline,sizeof(recvline));
	    bzero(sendline,sizeof(sendline));
	
	}	
}

int main()
{
	int sockfd;
	struct sockaddr_in server,client;
	socklen_t clilen;
	ssize_t n;

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(SERV_IP);
	server.sin_port=htons(SERV_PORT);

	dg_cli(sockfd,(struct sockaddr*)&server,sizeof(server));

}

