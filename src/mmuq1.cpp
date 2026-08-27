
#include <pthread.h>
#include <cstdio>

static int glob = 0 ; 
static pthread_mutex_t mm_t = PTHREAD_MUTEX_INITIALIZER;

static void* pthreadFunc(void* arg ) {
	int loops = *reinterpret_cast<int*>(arg); 
	for( int j = 0 ; j < loops ; j++) {
		/* here is where the vairable and the mutex hoding the lock blocks it */
	}
	return nullptr;
}
int main(){


	return 0 ;
}
