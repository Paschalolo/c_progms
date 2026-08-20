
#define _GNU_SOURCE 
#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <err_tlp_v1.h>
int main(int argc , char** argv ) {
	int fd ; 
	ssize_t numRead ; 
	size_t length , alignment  ; 
	off_t offset ; 
	char* buf ; 
	if(argc < 3 || (strcmp(argv[1] , "--help") == 0 ) ){
		errMsg("enter argunetns" , ERRMSG_NOSET , -1); 
	} 
	length = strtoul(argv[2] , NULL ,10);
	offset = strtol(argv[3] , NULL , 10);
	alignment = (argc > 4 ) ? strtoul(argv[4] , NULL ,10) : 4096ULL;
	
	fd  = open(argv[1] ,  O_RDONLY  | O_DIRECT) ;
	if(fd == -1 ) errMsg("open failed()" , ERRMSG_NOSET , -1);
	buf = aligned_alloc(alignment*2  , length+ alignment);
	if(buf == NULL) _exit(-1);
	buf += alignment ; 
	if(lseek(fd , offset ,SEEK_SET  ) == -1 ) errMsg("lseek error()",ERRMSG_NOSET , -1);

	numRead = read(fd , buf , length);
	if(numRead == -1 ) exit(1) ;
	printf("Read %ld bytes \n", numRead);
	return 0 ;
}
