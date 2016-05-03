#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>

#define SERV_PORT 9002

int main()
{

  char str[INET_ADDRSTRLEN],*str1,*str2;
  struct sockaddr_in server;
  //server.sin_port=SERV_PORT;
    
  // store this IP address in server:
  printf("Testing inet_pton and inet inet_ntop\n");
  inet_pton(AF_INET, "192.0.2.33", &(server.sin_addr));
  // now get it back and print it
  inet_ntop(AF_INET, &(server.sin_addr), str, INET_ADDRSTRLEN);
  printf("%s\n", str); // prints "192.0.2.33"
  
  bzero(&str1,sizeof(str1));
  bzero(&server,sizeof(server));
  printf("Testing inet_ntoa and inet_aton\n");
  
  inet_aton("192.168.1.1",&(server.sin_addr));
  str1=inet_ntoa(server.sin_addr);
  printf("%s\n",str1);


  bzero(&str1,sizeof(str1));
  bzero(&server,sizeof(server));
  printf("Testing inet_addr\n");
  
  server.sin_addr.s_addr=inet_addr("192.2.2.2");
  str2=inet_ntoa(server.sin_addr);
  printf("%s\n",str2);

  
}

