
#define _GNU_SOURCE 
#include <signal.h>
#include <unistd.h>
#include <sys/signalfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
	sigset_t mask ; 
	int sfd   ; 
	struct signalfd_siginfo fdsi ;
	ssize_t ssz ; 

	printf("PID : %d\n" , getpid());
	sigemptyset(&mask); 
	sigaddset(&mask, SIGINT);
	sigprocmask(SIG_BLOCK , &mask , NULL); 

	sfd = signalfd(-1 , &mask , 0 ); 
	if(sfd ==-1) exit(-1);

	for(;;){
		ssz = read(sfd , (char*)&fdsi , sizeof(struct signalfd_siginfo));
		if(ssz != sizeof(struct signalfd_siginfo)){
			return -1;
		}
		printf("%s : got signal %d " , strsignal((int)fdsi.ssi_signo) , fdsi.ssi_signo);
	}
	return 0;
}
