


#include <bits/types/struct_timeval.h>
#include <cerrno>
#include <sys/time.h>
#include <signal.h>
#include <cstdio>
#include <time.h>
#include <stdlib.h>
static void sigHandler(int){

	return ; 
}

int main(){

	struct timeval start , finish ; 
	struct timespec request , remain ;
	struct sigaction sa = {};
	int s ; 
	request.tv_sec = 10 ; 
	request.tv_nsec = 100 ;

	/* Allow sighandler to intterupt the nanosleep()*/
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &sigHandler;

	if(sigaction(SIGINT , &sa , nullptr) == -1 ) {
		exit(-1);
	}

	if(gettimeofday(&start , nullptr) == -1 )exit(-2);

	for(;;){
		s = nanosleep(&request , &remain);
		if(s ==-1 && errno == EINTR){
				exit(-10);
		}

		if(gettimeofday(&finish , nullptr) == -1 ){exit(-1);}
		std::printf("Slept for %9.6f secs \n" , (static_cast<double>(finish.tv_sec - start.tv_sec) + (static_cast<double>(finish.tv_usec - start.tv_usec)/1000000.0f)));
		if(s == 0 ) break ; 
		printf("Remaining : %2ld.%09ld\n" , remain.tv_sec, remain.tv_nsec);
		request = remain ; 
	}

	printf("Sleep complete\n");
	return 0 ; 
	}
