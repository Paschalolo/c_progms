
#include "err_tlp_v1.h"
#include <tlp_v1.h>
#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>


int main(int argc , char** argv){
	size_t len ; 
	off_t offset  ; 
	int fd , ap , j ; 
	char* buf ; 
	ssize_t numRead , numWritten ; 


	if(argc < 3 ) {
		errMsg("input the files " , ERRMSG_NOSET , -1);
	}

	fd = open(argv[1] , O_RDWR | O_CREAT , S_IRWXU);
	if(fd == -1 ) errMsg("open error ()\n" , ERRMSG_NOSET , -1);


	for(ap = 2 ; ap < argc ; ap++){
		switch(argv[ap][0]){
			case 'r' : 
			case 'R' : 
				len = strtoul(&(argv[ap][1]), NULL, 10);
				if(len == 0) {errMsg("COuldnt convert message \n", ERRMSG_NOSET,-1);}
				buf = malloc(len) ; 
				if(buf == NULL) {
				exit(-1);	
				}
				numRead = read(fd , buf , len);
				if(numRead == - 1){
				errMsg("read() \n", ERRMSG_NOSET,-1);
				}

				free(buf);
				break ; 
		}
	}
	return 0;
}
