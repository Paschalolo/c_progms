
#include <sys/socket.h>
#include <unistd.h>
#include <unp.h>


int main(){
	int sockfd ; 
	struct sockaddr_in srvaddr {}; 
	srvaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	srvaddr.sin_port = htons(8080) ; 
	srvaddr.sin_family = AF_INET ;

	if((sockfd = socket(AF_INET , SOCK_DGRAM, 0)) == -1 ){
		err_sys("spcket failed() \n");
		}
	ssize_t n ;
	if(connect(sockfd,reinterpret_cast< const struct sockaddr *>(&srvaddr), sizeof srvaddr) < 0 ) {
		err_sys("doncnect failed");
	}
	for(int i{0} ; i < 4096 ; i++){
		if( (n = write(sockfd , "Hello world" , 12)) ==  -1 ) {
			err_sys("failed");
		}
	}
	return 0;
}
