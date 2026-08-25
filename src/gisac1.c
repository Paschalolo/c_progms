#define   _GNU_SOURCE 
#include <signal.h>
#include <stdio.h>
#include <unistd.h>


static void sigHandler(int, siginfo_t* , void* ){
	printf("signal interrupt\n") ;
}
int main(){
	struct sigaction sigac ={0};
	sigac.sa_sigaction = &sigHandler;
	sigac.sa_flags = SA_SIGINFO;
	sigaction(SIGINT , &sigac, NULL);
	int i = 0 ; 
	while(1){
		sleep(3);
		printf("%d\n" , i++ ) ;
	}
		return 0;
}
