#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>



int main(int argc , char** argv ){
	struct stat stb ; 
	off_t len ; 
	char* ptr ; 
	int fd ; 
	if(argc < 2 ) {
		return -2;
	} 
	fd = open(argv[1] , O_RDONLY);

	if(fd == -1 ){
		fprintf(stderr , "Open fsailed "); 
		return -2;
	}
	if(fstat(fd ,&stb)== -1){close(fd);return -2 ;}
	if(!S_ISREG(stb.st_mode)){
		fprintf(stderr , "not a regular file"); 
		return -3;
	}
	ptr = mmap(NULL ,(size_t)stb.st_size , PROT_READ , MAP_SHARED , fd , 0 );
	if(!ptr){
		return -4;
	}
	
	close(fd);
	munmap(ptr ,(size_t) stb.st_size );
	return 0;
	}
