

#include <bits/types/struct_timeval.h>
#include <sys/time.h>
#include <cstdio> 
#include <signal.h>
#include <time.h>
#include <stdlib.h>


static volatile sig_atomic_t gotAlarm = 0 ; 


static void displayTimes(const cahr* msg , bool includeTimer){
	struct itimerval itv ; 
	static struct timeval start ; 
	struct timeval curr ; 
	static int callNum = 0 ; 

	if(callNum == 0) {
		if(gettimeofday(&start , nullptr) ==-1 ) {
			exit(-1);
		}
	}
	if(callNum % 20 ) {
		std::printf("\tElapsed Value internal\n");

		if(gettimeofday(&curr , nullptr)== -1) {
			exit(-1);
		}
		std::printf("%-7s %6.2f", msg , (curr.tv_sec -start.tv_sec) + ((curr.tv_sec - start.tv_sec)/1000000.0f));
	}
}
