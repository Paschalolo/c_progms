

#include <unistd.h>
#include <cstdio>
static int idata1 {111};
int main(){
	int istack {222};
	pid_t childpid ; 


	switch(childpid = fork()){
		case -1:
			_exit(-1);
		case 0 :
			idata1 *= 3 ; 
			istack *= 3 ;
			break ;
		default : 
			sleep(3);
			break ;
	}
	printf("PID = %d %s idata = %d , istack = %d\n" , getpid() ,(childpid == 0 ) ? "(child)":"(parent)", idata1 ,istack);
	return  0 ;
}
