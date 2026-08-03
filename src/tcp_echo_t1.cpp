
#include <cstring>
#include <netinet/in.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <unp.h>
#include <limits.h>
int main(){
	int i , maxi , listenfd , connfd , sockfd ; 
	int nready ; 
	ssize_t n ; 
	char buf[MAX_LINE] ; 
	struct pollfd client[5] ; 
	struct sockaddr_in clientadr , srvaddr ;

	if ( (listenfd = socket(AF_INET , SOCK_STREAM , 0)) == -1){
		err_sys("socket() failed");
	}

	std::memset(reinterpret_cast<void*>(&srvaddr) , 0x00 ,sizeof srvaddr );
	srvaddr.sin_addr.s_addr = INADDR_ANY; 
	srvaddr.sin_port = htons(8080); 
	srvaddr.sin_family = AF_INET ;

	if(bind(listenfd , reinterpret_cast<const struct sockaddr *>(&srvaddr) , sizeof srvaddr) == -1 ){
		err_sys("bind() failed");
	}
	
	if(listen(listenfd , BACK_LOG) == -1 ){
		err_sys("listem()");
	}

	client[0].fd = listenfd; 
	client[0].events = POLLIN ; 
	for(auto j{1uz} ; j < 5 ; j++){ client[j].fd = -1;}

	for(;;){
		nready = poll(client , 1 , -1) ; 
		if(client[0].revents & POLLIN){	
			connfd = accept(listenfd , reinterpret_cast<struct sockaddr*>(&clientadr) , nullptr);

		}
	}
	return 0;

}
