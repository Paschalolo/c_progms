



#include <sys/select.h> 
#include <sys/time.h> 
#include <unistd.h>
#include <sys/types.h>
#include <cstdio>


int main(){
	struct timeval tv{}; 
	fd_set readfds ; 
	FD_ZERO(&readfds) ; 
	FD_SET(STDIN_FILENO, &readfds);
int ret ;
	tv.tv_sec = 5 ; 
	tv.tv_usec = 0 ;

	ret = select(STDIN_FILENO+1  ,&readfds ,  nullptr , nullptr ,&tv );

	if(ret == -1){
		return -1;
	}else if (!ret){
		std::fprintf(stderr , "No discripore after waiting ");
		return 0 ; 
	}

	if(FD_ISSET(STDIN_FILENO , &readfds)){
		char buf[512]; 
		ssize_t len ; 
		len = read(STDIN_FILENO , buf ,512ULL-1ULL  );

		if(len == -1 ) {
		return 1;
		}
		buf[len] = 0x00 ;
		std::printf("read : %s\n", buf);
	}

	std::printf("None of that stuff above happened we where just playing\n");


	return 0;
}
