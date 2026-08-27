
#include <csignal>
#include <cstdlib>
#include <sched.h>
#include <signal.h>
#include <cstdio>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <err_tlp_v1.h>
#ifndef CHILD_SIG 
#define CHILD_SIG SIGUSR1 /* user defined signal */
#endif

static int childFunc(void* arg){
	if(close(*reinterpret_cast<int*>(arg)) == -1) {
		std::fprintf(stderr , "clsoe failed()\n");
		exit(1);
	}
	return 0;
}

int main(){
	constexpr int STACK_SIZE = 65536 ; 
	char* stack , *stacktop ; 
	int  fd , flags ; 

	fd = open("/dev/null" , O_RDWR , S_IRWXU );
	if(fd == -1 ) exit(1);
	flags = CLONE_FILES ; 
	stack = reinterpret_cast<char*>(malloc(static_cast<size_t>(STACK_SIZE)));
	if(stack == nullptr) {
		errMsg("stack allocation failed\n" , ERRMSG_NOSET , -1);
	}
	stacktop = stack + STACK_SIZE ;
	if (CHILD_SIG != 0 && CHILD_SIG != SIGCHLD) {
		if(signal(CHILD_SIG , SIG_IGN) == SIG_ERR) exit(-1);
	}

	/* create the child */ 
	if (clone(&childFunc , stacktop , flags| CHILD_SIG , reinterpret_cast<void*>(&fd)) == -1 ) {exit(1);}

	if(waitpid(-1 ,nullptr , (CHILD_SIG != SIGCHLD) ? __WCLONE : 0) == -1 ){exit(1);} 

	printf("child ahs succesfull been terminated ");
	/* free allocated memeory */ 

	auto s= write(fd , "x" , 1 ) ; 
	if ( (s== -1)  & (errno ==   EBADF) ){
		std::printf("FIle descriptor has been closed\n") ;
	}else if (s == -1 ) {
		std::printf("unsexpectedly \n");
	}else {
		std::printf("Write top file succeedded \n");
	}
	std::free(stack);
	return  0 ;
}
