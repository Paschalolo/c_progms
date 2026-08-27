
#include <pthread.h>
#include <cstdio>
#include <sched.h>
#include <unistd.h>

pid_t my_pthread_self(){
	return getpid();
}
int main(){
	std::printf("%lu : %d \n" , static_cast<unsigned long>(pthread_self()) , my_pthread_self());
}
