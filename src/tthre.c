#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
void* start_thread([[maybe_unused]] void* arg){
	printf("%s " , (char*) arg );
	return arg ; 
}

__attribute__((cold , noinline)) void fin(){
	fprintf(stderr , "Finisto");
	exit(1);
}
int main(){
 int ret ; 
 	pthread_t thrd1 , thrd2 ;
	const char name[] = "Thing1" ; 
	const char name1[] = "Thing1" ; 
	ret = pthread_create(&thrd1 , NULL , &start_thread , (void*) name) ;
	if(ret == -1 ) fin();
	ret =pthread_create(&thrd2 , NULL , &start_thread , (void*) name1) ; 
	
	if(ret == -1 ) fin();
	ret = pthread_join(thrd1 , NULL);

	if(ret == -1 ) fin();
	pthread_join(thrd2 , NULL);
	return 0;
}
