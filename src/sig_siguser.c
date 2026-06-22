/*
 *	Signal -- using the SIGUSR1 signal as a command to do a clean shutdown 
 *	Use two parent and child process 
 *	Copyright(c) 2024-2026 
 * */


#include <stdio.h> 
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int sig_handler(int sig){
	fprintf(stdout , "In signal handler() , this process reciveed by a signal %d" , sig);
	printf("this process si shutting down");
	exit(0 );
}
int main(){
	pid_t pid ; 
	int stat;
	pid = fork();
	if(pid == 1 ) {
		fprintf(stderr , "fork() failed errno = %d\n", errno);
		return -1;
	}
	else if(pid == 0 ){
		struct sigaction newact , oldact; 
		fprintf(stdout , "Child is born \n"); 
		sigfillset(&newact.sa_mask);
		newact.sa_flags = 0 ;
	}

	return 0;
}
