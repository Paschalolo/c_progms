
#include <sys/resource.h>
#include <sys/time.h>
#include <cstdio>
#include <unistd.h>


int main(){
	int prio ; 
	prio = getpriority(PRIO_USER , getuid()) ; 
if(prio == -1 ) {return -1;}
	std::printf("%d" , prio);
	return 0 ;
}
