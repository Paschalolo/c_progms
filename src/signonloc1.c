

#define _GNU_SOURCE 
#include <signal.h>
#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include <stdlib.h>

static volatile sig_atomic_t canJump = 0 ; 
static jmp_buf env ; 
static void sigHandler(int sig ) {

	printf("Received signal %d : %s\n", sig ,  strsignal(sig));
	if(!canJump){
		printf("Cannot jump doing a ismple return \n");
		return ; 
	}

	longjmp(env,1);
}
int main(){
	struct sigaction sa ={0};
	sa.sa_handler = &sigHandler; 
	if(sigaction(SIGINT , &sa , NULL )== -1) {
		return -2;
	}

	printf("calling sig jump ");

	canJump =1;

	if(setjmp(env ) == 1){
		printf("finni\n");
		exit(0);
	}
	for(;;) {
		printf("how dy\n");
		sleep(3);}
	return 0 ;
}
