
#include <stdio.h>
#include <pthread.h>
#include <time.h>


void* child_thread([[maybe_unused]]void* arg) {
	printf("Enter the child thread");
	printf("Exiting the child thread");
	pthread_exit((void*)NULL);
}


int main(){
	pthread_t thrd ; 
	int ret = 0 ; 

	/* Create a child thread to run the child thread */ 
	ret =pthread_create(&thrd , (pthread_attr_t*)NULL ,(void*(*)(void*))child_thread ,(void*) NULL  );
	if(ret != 0 ) {
		fprintf(stderr, "Failed to create the thread\n");
		return -1 ; 
	}

	ret = pthread_join(thrd , (void**)NULL);

	if(ret == -1){
		fprintf(stderr , "Error failed to join the child thread");
	}
	printf("Main thread exiting");
	return 0;
}
