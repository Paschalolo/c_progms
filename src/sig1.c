
#define _DEFAULT_SOURCE 
#include <signal.h>
#include <stdio.h>
#include <err_tlp_v1.h>
#include <unistd.h>
static void signalHandler([[maybe_unused]]int sig) {

	printf("Ouch\n");
}

static void sigQUITTER(int){

	printf("caught ISGQUIT bye now \n") ;
	_exit(0);
}

static void sigtermm(int){
	printf("segfault caught");
}

int a[2] = {1,12 };
int main(){

	int j ; 
	if(signal(SIGINT , &signalHandler) == SIG_ERR){
	errMsg("Signal call failed ", ERRMSG_NOSET , -1)	;
	}

	if(signal(SIGQUIT , &sigQUITTER) == SIG_ERR){
	errMsg("Signal call failed ", ERRMSG_NOSET , -1)	;
	}
	signal(SIGSEGV , &sigtermm) ;

	int* pop = (int*)0xFF11223344ULL;
	j = *pop;
	for( ; ; j++) {
	printf("%d\n" , j ) ; 
	sleep(3);
	}

	return 0 ; 
}
