

#include <asm-generic/socket.h>
#include <bits/types/struct_timeval.h>
#include <cerrno>
#include <cstring>
#include <memory>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unp.h>



int main(){
	int sockfd ; 
	struct sockaddr_in srvaddr {}; 
	struct sockaddr_in clntaddr {}; 
	if((sockfd = socket(AF_INET , SOCK_DGRAM , 0)) == -1 ){
		err_sys("SOCket() failed\n");
	}

	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY) ; 
	srvaddr.sin_port = htons(8080);
	srvaddr.sin_family = AF_INET ;

	if(bind(sockfd ,  reinterpret_cast<const struct sockaddr*>(&srvaddr) , sizeof srvaddr) <0){
		err_sys("bind() faield ");
	}
	char buf[MAX_LINE +1] ;
	ssize_t ret ;
	socklen_t len ;
	int count = 0;
	constexpr size_t MAXC = 4096;
	struct timeval tv {5,0};
	setsockopt(sockfd, SOL_SOCKET ,SO_SNDTIMEO  , reinterpret_cast<void*>(&tv), sizeof(struct timeval) );
	setsockopt(sockfd, SOL_SOCKET ,SO_RCVTIMEO  , reinterpret_cast<void*>(&tv), sizeof(struct timeval) );
	for(;;){
		if((ret = recvfrom(sockfd,buf,MAX_LINE-1,0, reinterpret_cast<struct sockaddr *>(&clntaddr),&len)) == -1){
			if((errno == EAGAIN) || (errno == EINPROGRESS)){
				break;
			}else{continue;}
		}
		count++;

	}
	std::printf("packcets sent to server : %lu , packets received %d" ,MAXC , count );
	close(sockfd);
	return 0;
}
