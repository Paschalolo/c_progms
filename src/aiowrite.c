/*
 *	This program opens a file and writes a  nuber of KBs to it using 
 *	asynchronous IO
 *	Copyright (c) 
 * */

#include <asm-generic/errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <aio.h>
#include <sys/stat.h>

#define BUFSZ (100 * 1024)
char buf[BUFSZ] = {0};
int main(int argc , char** argv ){

	char* fname ; 
	int fd ; 
	ssize_t bytes ; 
	size_t count ; 
	int status ; 
	int nkbs = 20 ; 
	struct aiocb aiocb ; 
	/* Exepect ro get file from user */ 

	if(argc > 1 ) {
		fname = argv[1]; 
	}else {
		fprintf(stderr, "usage %s filename ",argv[0]);
		return -1;
	}

	if(argc > 2) {
		nkbs = atoi(argv[2]);
		if((nkbs <= 0) || (nkbs > 100)){
			nkbs = 1 ;
		}
	}
	printf("Writng %u KBS to file %s\n", nkbs , fname);

	fd = open(fname , O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if(fd == -1 ) {
		return -2;
	}

	count = (size_t)nkbs * 1024 ; 
	/* FIll aio control block*/
	aiocb.aio_fildes = fd ; 
	aiocb.aio_buf = buf;
	aiocb.aio_nbytes = count; 


	/* write ammount speciidfed tro the file */ 
	status = aio_write(&aiocb);
	if(status == -1 ) {
		fprintf(stderr , "The aio requesr has not been enqueed");
		close(fd);
		return -2;
	}else if(status ==  0 ) {
		printf("The aio request has been enqueed ") ; 
	}


	status = EINPROGRESS ; 
	while(status == EINPROGRESS) {
		status = aio_error(&aiocb);} 
	switch(status){
		case 0: 
			printf("the request is sucesfully finshed");
			break ; 
		case ECANCELED : 
			printf("The async io was cancelled");
			break ;
		default : 
			printf("An error occured");
			break ;
	}
	bytes = aio_return(&aiocb) ; 
	if(status == -1) {
		fprintf(stderr , "coudlnot read from the file");
		close(fd) ; 
		return -3;
	}

	printf("%ld vytes where written ", bytes);
	close(fd);

	return 0;

}
