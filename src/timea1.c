#include <err_tlp_v1.h>
#include <sys/times.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
int main(int argc , char** argv ) {
	if(argc < 1 ) {printf("failed ha");return -1;}
	if(execv(argv[0] , &argv[1]) == -1 ){
		fprintf(stderr , "failed %s \n", strerror(errno)) ;
	}

	struct tms tt ; 
	if((clock_t)-1 == times(&tt)) {errMsg("failed hmm" , ERRMSG_SET , -1);}
	printf("user time : %ld " , tt.tms_utime);
	printf("system time : %ld " , tt.tms_stime);
}
