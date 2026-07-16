
 #include <sys/epoll.h> 
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


int main(){
	int efd ;
	int fd ;
	struct epoll_event evnt ; 
	int ret ; 
	efd = epoll_create1(0);
	if(efd == -1 ){
		fprintf(stderr , "Epoll() failed");
		return -2;
	}
	fd = open("loyal.txt", O_RDWR );
	if(fd == -1 ){
		return -4 ; 
	}
	evnt.data.fd = fd ; 
	evnt.events = EPOLLIN ;

	ret = epoll_ctl(efd  , EPOLL_CTL_ADD ,fd , &evnt );
	if(ret == -1 ) {
		close(fd);
		close(efd);
		return -1;
	}

	while(true){
		ret = epoll_wait(efd , &evnt, 1 , 1000);
		if(ret == -1) {
			break ; 

		}
		if(ret > 0 ) {
			printf("%u" , evnt.events) ;
			printf("%d -> fd " , evnt.data.fd);
		}
	}
	close(efd); 
	close(fd);
	return 0;
}
