#include <stdio.h>
#include <pthread.h>


constexpr int  NTHREAD =  4; 
constexpr int NTASKS = 500'000 ; 
constexpr int DELAY_COUNT = 1000 ; 

unsigned int global_count = 0 ; 
pthread_mutex_t mutex   ;

/* The worker thread */ 
void* worker_thread(void* args){
	auto argp = (unsigned int*) args;
	unsigned int myid ; 
	unsigned int tasks ; 
	if(argp != NULL) {
		myid = argp[0];
		tasks = argp[1] ; 
	}else{
		return (void*)-1;
	}
		printf("Worker thread : myid -> %u ntasks = %u\n", myid , tasks);

}
