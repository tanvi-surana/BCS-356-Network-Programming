#include <stdio.h>
#include <signal.h>
 
/* Signal Handler for SIGINT */
void sigintHandler(int sig_num)
{
    // Reset handler to catch SIGINT next time.
       
    signal(SIGINT, sigintHandler);
    printf("\n Cannot be terminated using Ctrl+C \n");
    fflush(stdout);
}
 
int main ()
{
    // Set the SIGINT (Ctrl-C) signal handler to sigintHandler 
       
    signal(SIGINT, sigintHandler);
 
    /* Infinite loop */
    while(1)
    {        
    }
    return 0;
}
