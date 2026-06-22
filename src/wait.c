
/*
 * Create a child process and wait for them to exit 
 * */

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>


#define NPROCS 2 /* number of child process to create */ 

int main(){
	pid_t pid ; 
	int i ; 
	int stat ; 
	printf("Parent to create %u child child process\n", NPROCS);
	for(i = 0 ; i < NPROCS ; ++i){
		pid = fork(); 
		if(pid == -1 ){
			return -1;
		}else if(pid == 0 ){
			fprintf(stdout , "I am the new born child\n");
			fprintf(stdout , "my parent is %u\n", getppid());
			sleep(2); 
			return 0;
		}

	}
	/* This si the parent*/ 
	kill(pid, SIGKILL) ; 

}
