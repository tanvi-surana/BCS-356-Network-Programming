#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<error.h>
#include<netinet/in.h>	
#include<sys/select.h>	

#define MAXLINE 1001
#define SERV_PORT 9002

int main()
{
	int listenfd,connfd,sockfd;
	int nready,client[FD_SETSIZE]={-1};
	int maxfd,i,maxi;
	ssize_t n;
	fd_set rset,allset;
	char buff[MAXLINE];
	
	struct sockaddr_in server,clientaddr;

	listenfd=socket(AF_INET,SOCK_STREAM,0);
	bzero(&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=htons(SERV_PORT);

	bind(listenfd,(struct sockaddr*)&server,sizeof(server));
	listen(listenfd,5);

	maxfd=listenfd;
	maxi=-1;

     	FD_ZERO(&allset);
     	FD_SET(listenfd,&allset);

	 

    for(;;){
   // 	printf("Entering\n");
    	rset=allset;
    	nready=select(maxfd+1,&rset,NULL,NULL,NULL);
        if(FD_ISSET(4,&rset))
           printf("connfd set\n");
        printf("The value of nready is %d\n",nready);  
    	if(FD_ISSET(listenfd,&rset))
         {                 /*New client connection*/
    	    
    	    printf("Entering the FD_ISSET condition\n");  
            socklen_t clilen=sizeof(clientaddr);
            printf("before accept");
    	    connfd=accept(listenfd,(struct sockaddr*)&clientaddr,NULL);
    	    printf(" accept called %d\n",connfd);
    	    for(i=0;i<FD_SETSIZE;i++){
    	    	if(client[i]<0){
    	    		client[i]=connfd;
    	    		break;
    	    	}
    	    }

    	    if(i==FD_SETSIZE)
    	    {
    	    	perror("Too many clients");
    	    } 	


    	    FD_SET(connfd,&allset);     /*Add new descriptor to the set*/
            
            if(connfd>maxfd)
            	maxfd=connfd;           /* for select */

            if(i>maxi)
               maxi=i;                  /* max index in the client array */

            if(--nready<=0)
               continue;     	

    	}



	    for(i=0;i<=maxi;i++){
	    	if(sockfd=client[i]<0)
	    		continue;
	    	 if(FD_ISSET(sockfd,&rset))
                 {
                    if((n=recv(client[i],buff,MAXLINE,0))==0){
                  /* connection closed by client */
                    close(sockfd);
                    FD_CLR(sockfd,&allset);
                    client[i]=-1;

                 }
                 else
		{
      //           printf("sending data to the client\n");
               	   send(client[i], buff ,strlen(buff), 0);
               	   printf("%s",buff);
                }  
                if(--nready<=0)
               	 break;             /* No more readable descriptors */

	           }
	    	}

    }





}
