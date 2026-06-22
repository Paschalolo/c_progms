/*
 *
 *	sIG DEFAULT 
 * */

#include <stdio.h>
#include <errno.h>
#include <signal.h>


int main(){
	int ret ; 
	struct sigaction oldact , newact ; 

	sigfillset(&newact.sa_mask); 
	newact.sa_flags = 0 ; 
	ret = sigaction(SIGQUIT , &newact, &oldact);

	if(ret != 0 ) {
		return -1;
	}
	fprintf(stderr, "Please send a sigaction signals ");
	while(1){}
}
