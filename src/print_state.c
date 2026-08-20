#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h> 

__attribute__((noinline , cold)) void err_exit(int a) {

	exit(a);
}

constexpr size_t SZ = 1024 ;
int main(){
	int fd ; 
	ssize_t rett ; 
	if((fd = open("/proc/self/status" , O_RDONLY ,  S_IRWXU )) == -1 ){
		err_exit(-1);
		}
	char* alloc_buf  = (char*)aligned_alloc(8,SZ );
	if(alloc_buf == NULL) {
		return -4 ;
	}
	if( (rett = read(fd , alloc_buf ,SZ))  < 1 ){
		free(alloc_buf) ; 
		fprintf(stderr , "read failed %s \n" , strerror(errno));return -3;
	}
	alloc_buf[rett] = 0x00 ;
	printf("%s", alloc_buf);
	free(alloc_buf) ; 
	return 0 ; 
}
