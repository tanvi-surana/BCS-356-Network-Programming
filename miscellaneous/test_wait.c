#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    pid_t   pid;
    int     status;

    if ((pid = fork()) < 0)
        printf("fork error");
    else if (pid == 0)              /* child */
        exit(7);

    if (wait(&status) != pid)       /* wait for child */
        printf("\nwait error");
	printf("\n status=%d\n",status);                /* and print its status */
	
	status=0;
    if ((pid = fork()) < 0)
        printf("\nfork error");
    else if (pid == 0)              /* child */
        abort();                    /* generates SIGABRT */

    if (wait(&status) != pid)       /* wait for child */
        printf("\nwait error");
    printf("\n status=%d\n",status);                /* and print its status */                 
status=0;
    if ((pid = fork()) < 0)
        printf("\nfork error");
    else if (pid == 0)              /* child */
        status /= 0;                /* divide by 0 generates SIGFPE */

    if (wait(&status) != pid)       /* wait for child */
        printf("\nwait error");
        	printf("\n status=%d\n",status);                /* and print its status */              

    exit(0);
}

