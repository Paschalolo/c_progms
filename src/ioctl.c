
/*
 *	Read from the tereminal 
 *	Enables non blovcking io using ioctl() function
 *	By default blocking I/O is used when reading from the terminal 
 *	Pass in arguments to turn on nonblocking i/o 
 *	Copyright (c) Mr Paschal Ahanmisi . All Rights reserved 
 * */

#include <asm-generic/ioctls.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>


#define BUFSZ 256 

int main(int argc , char** argv){
	int ret ;
	char buf[BUFSZ] ; 
	ssize_t nbytes ;
	int fd = 0 ; 
	int flags ; 
	int nbio =0 ; 


	if(argc > 1) {
		nbio = 1 ; 
		printf("NOn blocking IO is on");
	}else{
		printf("Non blocking IO is off");
	}

	if(nbio) {
		flags = 1 ; 
		ret = ioctl(fd, FIONBIO, flags);
		if(ret == -1)return -1;
	}
	
	sleep(3);

	ret = ioctl(fd , FIONREAD , &nbytes);
	if(ret == -1) return -4;
	return 0;
}
