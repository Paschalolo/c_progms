

#include <memory>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unp.h>



int main(){
	int sockfd ; 
	struct sockaddr_in srvaddr {}; 
	if((sockfd = socket(AF_INET , SOCK_DGRAM , 0)) == -1 ){
		err_sys("SOCket() failed\n");
	}

	srvaddr.sin_addr.s_addr = INADDR_ANY ; 
	srvaddr.sin_port = htons(8080);
	srvaddr.sin_family = AF_INET ;

	if(bind(sockfd ,  reinterpret_cast<const struct sockaddr*>(&srvaddr) , sizeof srvaddr) <0){
		err_sys("bind() faield ");
	}
	char buf[MAX_LINE] ;
	ssize_t ret ;
	for(;;){
		if((ret = recvfrom(sockfd,buf,MAX_LINE,0, reinterpret_cast<struct sockaddr *>(&srvaddr),nullptr)) < 0){
			std::printf("err reading from udp client\n ");
			continue;
		}
		buf[ret] = 0x00 ; 
		if(sendto(sockfd , buf , static_cast<size_t>(ret) , 0, reinterpret_cast<const struct sockaddr*>(&srvaddr) , sizeof srvaddr) == -1 ){
			std::fprintf(stderr , "Could not wirte to clietn \n");
		}

	}
	return 0;
}
