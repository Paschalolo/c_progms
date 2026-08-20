#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h> 

__attribute__((noinline , cold)) void err_exit(int a) {

	exit(a);
}
int main(){
	int fd ; 
	ssize_t rett ; 
	if((fd = open("/proc/self/status" , O_RDONLY , S_IRUSR )) == -1 ){
		err_exit(-1);
		}
	struct stat buf ; 
	if(fstat(fd , &buf) == -1) return -2;
	printf("%ld" ,buf.st_size);
	char* alloc_buf  = (char*)aligned_alloc(8, (size_t)buf.st_size);
	if(!alloc_buf) {
		return -4 ;
	}
	if( (rett = read(fd , alloc_buf ,(size_t)buf.st_size ))  < 0 ){
		fprintf(stderr , "read failed %s \n" , strerror(errno));return -3;
	}
	alloc_buf[buf.st_size] = 0x00 ;
	printf("%s\n", alloc_buf);
	free(alloc_buf) ; 
	return 0 ; 
}
