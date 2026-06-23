#include <bits/pthreadtypes.h>
#include <bits/types/struct_sched_param.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>


void print_pthread_attr(pthread_attr_t* attr){
	int ret ; 
	int val = 0 ; 
	struct sched_param pri ; 
	void* stackaddr = NULL; 
	size_t stksz = 0 ; 
	size_t guardsz = 0 ; 

	if(attr == NULL) return ; 

	/* Get and print detached state*/

	ret = pthread_attr_getdetachstate(attr,&val); 
	if(ret == 0) {
		fprintf(stdout , "Detach state = %s\n", ((val == PTHREAD_CREATE_DETACHED) ? "PTHREAD_CREATE_DETACHED" : ((val == PTHREAD_CREATE_JOINABLE ) ? "PTHREAD_CREATE_JOINABLE" : "Unknown" )));
	}

	/* get and print inherit sceduler */
	
}
