/*
 *	Random write 
 *	Thsi program opens an existing file and write 5 bytes starting at the offset 512 aqnd then 
 *	writes anither 5 bytes at the file desccitor 1024
 * 	Copyright(c) Mr Paschal Ahanmisi
 * */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUFSZ 512
__attribute__((noinline , cold))int failed_io_call(const char* __restrict__ str ,int fd ,  int num){

		fprintf(stderr, "%s", str);
		close(fd) ;
		return  num ;
}
int main(int argc , char** argv ){

	int fd ; 
	char* fname ; 
	off_t offset, offset_ret ; 
	ssize_t bytes; 
	size_t count ; 
	char buf[BUFSZ] ;

	if(argc > 1) {
		fname = argv[1]; 
	}else {
		fprintf(stderr, "Usage %s filename \n", argv[0] );
		return -1;
	}
	// Open a file 
	fd = open(fname ,  O_RDWR ,S_IRWXU  );
	if(fd == -1 ) {
	fprintf(stderr, "couldnto open() file");
		return -2;
	}

	/* Write 5 bytes to offset 512 */ 
	offset = 512 ; 
	offset_ret = lseek(fd, offset,SEEK_CUR);
	if(offset_ret == -1) {
		fprintf(stderr, "Couldnnot find the seek position "); 
		return -2;
	}
	for(count = 0 ; count < 5 ; count ++){
		buf[count] = 'A';
	}
	bytes = write(fd , buf , 5);
	if(bytes == -1) {
	return	failed_io_call("write failed errono = %d", fd, -4);
	}

	offset = 1024 ; 
	offset_ret = lseek(fd, offset , SEEK_SET);
	if(offset_ret == -1) {
		return	failed_io_call("lseek() failed", fd, -6);
	}
	for(count = 0 ; count < 5 ;count++){
		buf[count] = 'B';
	}
	bytes = write(fd, buf, 5);
	if(bytes == -1){
		return	failed_io_call("write failed", fd, -7);
	}

	close(fd); 
	return 0;
}
