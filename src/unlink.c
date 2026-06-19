

/*
 *	Remove a file , symlink or hard link using the unlink() function 
 *	Copyright (c) 2024-2026 Mr Paschal Ahanmisi 
 *
 * */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc , char** argv){
	
	int ret ; char* fname ; 
	if(argc > 1) {
		fname = argv[1]; 
	}else {
		fprintf(stderr , "Usage : %s pathname \n", argv[0]);
		return -2;
	}
	ret = unlink(fname); 
	if(ret == - 1) {
		fprintf(stderr , "unlink failed() %d "  , errno) ;
		return -4;
	}
	return 0;
}
