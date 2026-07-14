#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>
__attribute__((cold, noinline)) void Kil_all_func(int errnum){
		fprintf(stderr , "Error occured at open %s" , strerror(errnum));
		exit(1);
}
void t1(){
	int fd ; 
	fd = open("home/kidd/madasgascar" , O_RDONLY);
	if(fd == -1)Kil_all_func(errno);
	fd = open("home/juj/hm" , O_WRONLY | O_CREAT | O_TRUNC , S_IWUSR | S_IRUSR | S_IWGRP) ;
	// ... below will be close()
	
}

void t2(){
	const char buf[] = "My ship is solid" ;
	ssize_t  nr ;
	int fd = 900 ;
	nr = write(fd , buf , strlen(buf)) ;
}
int main(){
	t1();
	return 0;
}
