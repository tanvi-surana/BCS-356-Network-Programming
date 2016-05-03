#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main(int argc, char const *argv[])
{
	int pid = fork();
	int status=0;
	//int s =wait(&status);
//	printf("\nIn code with pid = %d, the first status=%d\t%d\n", getpid(),status,s);
	if(pid==0)
	{
		printf("\nMy id :%d\n", getpid());
		sleep(20);
		printf("Parent id after sleep:%d\n", getppid());
		exit(0);

	}	
	int p=fork();
	if(p==0)
		exit(0);
	int s =wait(&status);
	printf("\nIn code with pid = %d, the first status=%d\t%d\n", getpid(),status,s);
	while(s>=0)
	{	s =wait(&status);
		printf("\nIn the second part of the code with pid = %d, the first status=%d\t%d\n", getpid(),status,s);
	}
	
		return 0;
}
