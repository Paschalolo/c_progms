

#include "err_tlp_v1.h"
#include <tlp_v1.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>


int main(int argc , char** argv ){
	int fd ; 
	struct iovec iov[3] ; 
	struct stat mystruct ; 
	int x ; 

#define STR_SIZE 100 
	char str [100] ; 
	ssize_t numRead , totorequried; 
	if(argc != 2 ) exit(1);

	fd = open(argv[1] , O_RDONLY);
	if(fd == -1 ) exit(1);
	
totorequried = 0 ; 
	iov[0].iov_base = (void*)&mystruct ; 
	iov[0].iov_len = sizeof mystruct;
	totorequried += (ssize_t) iov[0].iov_len ; 
	iov[1].iov_base = (void*)&x ; 
	iov[1].iov_len = sizeof x;
	totorequried += (ssize_t) iov[1].iov_len ; 
	iov[0].iov_base = (void*)str ; 
	iov[0].iov_len = (size_t)STR_SIZE;
	totorequried += (ssize_t)iov[2].iov_len ;

	numRead = readv(fd ,&(iov[0]) , 3 );
	
	if(numRead == -1 )errMsg("iovec failed readv\n" , ERRMSG_NOSET , -1); 

	if(numRead < totorequried) {
		printf("read fewer bytes than requested \n");
	}

	printf("Read totoal bytes requested :%ld bytes read : %ld " , totorequried , numRead);
	
	close(fd) ; 
	return 0;
}
