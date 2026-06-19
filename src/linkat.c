
/*
 *	link and linkat()
 *
 * *
 */
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 #include <unistd.h>
#include <string.h>

int main(int argc , char** argv){
	int ret ; 
	int fd ; 
	int flags = AT_SYMLINK_FOLLOW ;
	char* fname  = NULL ; 
	char linkname[128] = {0}; 


	/*Get name of the file*/
	if(argc > 1 ) {
	fname = argv[1] ; 	
	}else{
		fprintf(stderr, "Usage %s %s", argv[0] , argv[1]) ;
		return -1 ; 
	}
	printf("Creating two links of %s existinf file \n", argv[1]);
	fd = open(".", 0);
	if (fd < 0 ) {
		fprintf(stderr, "Open() failed ") ; 
		return -1; 
	}

	// create first linkn 
	strcpy(linkname , fname); 
	strcat(linkname , "_link1");
	ret = link(fname , linkname) ;
	if(ret < 0 ) return -3;  
	memset(linkname, 0x00 ,127);
	strcpy(linkname , fname); 
	strcat(linkname , "_link2"); 
	ret = linkat(fd , fname , fd , linkname  , flags);
	if(ret == -1) {
		return -4;
	}
	return 0;
}
