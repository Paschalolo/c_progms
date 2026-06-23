
/*
 *
 *	Passin an array of integers to a child thread and returning one integer 
 *	Copyright (c) @024 - 2026 Mr Paschal Ahanmisi
 * */

#include <stdio.h> 
#include <pthread.h>
#define NTHREAD 3 
#define NTASKS 3
/* The worker thread */ 
void* worker_thread(void* args){
	unsigned int* argp ; 
	unsigned int myid ; 
	unsigned int ntasks ;
#ifdef SUN 
	int ret = 0 ; 
#endif 
	argp = (unsigned int*)args ;
	if(argp != NULL) {
		myid = argp[0];
		ntasks = argp[1] ; 
	}else {
#ifdef SUN 
		ret = -1 ; 
		retunr ret ; 
#endif
	pthread_exit((void*)NULL); 
	}
	printf("Worker thread myid: %u and tasks : %u", myid , ntasks);
	return (void*)100 ;
}
int main(){
	pthread_t pthrd ; 
	unsigned int args[NTHREAD][2] ; 
	int ret , i ; 

	for(i = 0 ; i < NTHREAD ; i++){
		args[i][0] = 1; 
		args[i][1] = NTASKS ; 
	}

	/* CReate a new thread to run the worket threads and pass in the args */ 
	ret = pthread_create(&pthrd , (pthread_attr_t*)NULL , (void*(*)(void*))&worker_thread , (void*)args[1]);
	if(ret == -1) {
	return -1;
	}
	
	int ans ;
	pthread_join(pthrd, (void**)&ans);
	printf("Value returned is %d" , ans);
}
