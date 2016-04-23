#include<unistd.h>
#include<sys/socket.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<error.h>
#include<signal.h>
#include<errno.h>

#define SERV_PORT 9002
#define MAXLINE 1001


void err_sys(const char* x) 
{ 
    perror(x); 
    exit(1); 
}

void sig_chld(int signo)
{
  pid_t pid;
  int stat;

  while((pid=waitpid(-1,&stat,WNOHANG))>0) /* pid_t waitpid(pid_t pid, int *status, int options);*/
      printf("child %d terminated\n",pid);
  return;    
}


void str_echo(int sock_fd)
{
   ssize_t n;
   char buff[MAXLINE];

   while((n=read(sock_fd,buff,MAXLINE))>0)
   	{
   		printf("Echoing back... \n ");
   		write(sock_fd,buff,n);
   	}	

}


int main()
{
	int listenfd,connectfd;
	struct sockaddr_in server,client;
    pid_t child_pid;
    socklen_t clilen;
	if((listenfd=socket(AF_INET,SOCK_STREAM,0))<0)
      {
      	perror("Socket not created");
      }
     else
     {
     	printf("Socket created\n");
     } 		

      
     bzero(&server,sizeof(server));
     server.sin_family=AF_INET;
     server.sin_addr.s_addr=htonl(INADDR_ANY);
     server.sin_port=htons(SERV_PORT);

     if((bind(listenfd,(struct sockaddr*)&server,sizeof(server)))<0)
     {
     	perror("Bind failed");
     }
     else
     {
     	printf("Bind successful \n");
     } 
     
     listen(listenfd,5);
      
     signal(SIGCHLD,sig_chld);
      
     /*Daemon :D*/ 
     for(;;)
     {
     	//clilen=sizeof(client);
        if( (connectfd=accept(listenfd,(struct sockaddr*) NULL,NULL) )<0)
        {
          if(errno == EINTR)   /* Interrupted system call */
             continue;
           else
            err_sys("accept error");
        }


        if((child_pid=fork())==0)
        {
        	close(listenfd);
        	str_echo(connectfd);
            exit(0);   
                        
        }   
        close(connectfd);
     }	


}