
#define _GNU_SOURCE 

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#define MYFILE "./mychmodfile" 

int main(int argc , char** argv){
	int ret ; 
	struct stat finfo ; 
	char* pathname ; 

	if (argc > 1 ) {
		pathname = argv[1] ; 
		}else {
		pathname = MYFILE ; 
		}
	ret = stat(pathname , &finfo); 
	if(ret == -1) {
		return -2;
	}

	printf("access mode o%o", finfo.st_mode);
	ret = chmod(pathname ,finfo.st_mode | S_IWGRP | S_IWOTH );
	if(ret == -1) {
		return -2; 
	}

	ret = stat(pathname , &finfo); 
	if(ret == -1) {
		return -2;
	}

	printf("access mode o%o", finfo.st_mode);

		return 0;
}
