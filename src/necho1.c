
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
int main(int argc , char** argv ){
	int j ; 
	for(j =0 ; j < argc ; j++){

			printf("argv[%d] : %s\n" , j , argv[j]);
	}
	struct rlimit rp ; 
	getrlimit( RLIMIT_DATA, &rp);
	printf("rlimit data : %ld \n" ,rp.rlim_max );

}
