

#include "err_tlp_v1.h"
#include <tlp_v1.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>

/* Simple implemantation fo libiovec  for vectored io*/

struct p_iovec_t {
	char *iov_base ;
	size_t iov_len;
};

ssize_t readv_p(int fd , struct p_iovec_t* iov , int iovcnt ){
	ssize_t ret = 0 ;
	ssize_t bytes_read ;
	for(int i = 0 ; i < iovcnt ; i++){
		bytes_read = read(fd, iov[i].iov_base , iov[i].iov_len);
		if(bytes_read >= 0 ) {ret += bytes_read ; 
		}else if (bytes_read == -1){
			ret = -1 ; 
			break ;
		}

	}
	return ret ;
}
ssize_t writev_p(int fd , struct p_iovec_t* iov , int iovcnt ){
	ssize_t ret = 0 ; 
	ssize_t bytes_written ;
	for(int i = 0 ; i < iovcnt ; i++){
		bytes_written = write(fd , iov[i].iov_base , iov[i].iov_len);
		if(bytes_written >= 0) {ret += bytes_written ; 
		}else if(bytes_written == -1 ){
			ret = -1 ; 
			break ;
		}
	}
	return ret ;
}
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
