#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>


int main(){
	int pri = getpriority(PRIO_PROCESS, 0); 
	printf("pritotiy : %d", pri);
	return 0;
}
