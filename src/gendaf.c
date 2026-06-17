/*
 *	This program opens a file and writes a number of 512 bytes blocks to a file 
 *	It can be used to create data files for testing 
 *	Copyright (c) 2024-2026 Mr Paschal Ahanmisi
 *	
 * */
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#define FILE_BUFSZ 512 
#define DEFBLKCNT 62

int main(int argc , char** argv){

	char* fname ; 
	int fd ; 
	ssize_t bytes ; 
	char buf[FILE_BUFSZ] ; 
	int blocks = DEFBLKCNT ; /* Number of blocks to write */ 
	char ch ; 
	int i ,  j , k ; 
	char* bufadr ; 

	/* Expect to get file name from user */
	if(argc > 1) {
		fname = argv[1] ; 
	}else{
		fprintf(stderr , "Usage: %s Filename [blocks]\n" , argv[0]);
		return -1;
	}

	if(argc > 2 ) {
		blocks = atoi(argv[2]);
		if(blocks < 0 ){
			blocks = DEFBLKCNT;
		}
	}

	fprintf(stdout , "Writing %u blocks to file %s\n", blocks , fname );
	/*
	 * open the output fil . create it if it does not exist 
	 * Truncate the file to zero length if it already exist */

	fd = open(fname , (O_TRUNC | O_CREAT | O_WRONLY), (  S_IRUSR  | S_IWUSR |  S_IRGRP  | S_IWGRP |  S_IROTH | S_IWOTH));
	
	if(fd == -1 ) {
		fprintf(stderr, "open() failed");
		return -2;
	}

	/* Write the numebr of blocks */ 
	for(k = 0 ; k < blocks ; k++){

		i = k% 62 ; 
		if(i < 10 ) {
			ch = (char) ('0' + i); 
		}else if (i < 36 ) {
			ch = (char)('a' + i) ; 
		}else {
			ch = (char)('A' + i);
		}
	}

	/* Fill the buffer with the contents to the file */ 
	for(j = 0 ; j < FILE_BUFSZ ; j++){
		count = BUFSIZ ; 
		bufadr = buf; 
	}
}
