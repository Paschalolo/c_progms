
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define TIMEOUT 5 
#define BUF_LEN 1024 
int main(void){
	struct timeval  tv ; 
	fd_set readfd ; 
	int ret ; 
	FD_ZERO(&readfd);
	FD_SET(STDIN_FILENO , &readfd); 

	tv.tv_sec = TIMEOUT ; 
	tv.tv_usec = 0; 

		/* All right now block */ 
	ret = select(STDIN_FILENO + 1 , &readfd , NULL , NULL , &tv);
	
	if(ret == -1) {
		perror("%d has elapsed ");
		return 0;
	}
	
	if(FD_ISSET(STDIN_FILENO , &readfd)){
		char buf[BUF_LEN +1] ; 
		ssize_t len ; 
		/* guaranteed no tto block */ 
		len = read(STDIN_FILENO, buf, BUF_LEN); 
		if(len == -1) {return 1;}
		if(len){
			buf[len] = 0x00 ; 
			printf("read %s " , buf);
		}
		return 0;
	}
	fprintf(stderr , "this should not happend");
	return 0;
}
