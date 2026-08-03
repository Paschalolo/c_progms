

#include <cerrno>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <cstdio>
#include <unistd.h>
int main(){
	struct sockaddr_in srvaddr{} ; 
	int sockfd ; 
	int connfd ; 
	if((sockfd = socket(AF_INET , SOCK_STREAM , 0)) == -1 ){
		return -1;
	}
	srvaddr.sin_addr.s_addr = INADDR_ANY ; 
	srvaddr.sin_port = htons(8080); 
	srvaddr.sin_family = AF_INET;
	
	if(bind(sockfd , reinterpret_cast<const struct sockaddr*>(&srvaddr), sizeof srvaddr)){return -2;}
	if(listen(sockfd , 1024) == -1 ) {return -3;}
	int optval = 1 ;
	int mkeepcnt = 1 ;
	int m_keepidle = 10 ; 
	int m_kintp = 10 ;
	struct timeval tv{1,0} ;
	setsockopt(sockfd ,SOL_SOCKET,SO_KEEPALIVE ,&optval , sizeof optval );
	setsockopt(sockfd ,SOL_SOCKET,SO_RCVTIMEO,&tv , sizeof optval );
	setsockopt(sockfd ,IPPROTO_TCP, TCP_KEEPCNT  , &mkeepcnt , sizeof optval );
	setsockopt(sockfd ,IPPROTO_TCP,TCP_KEEPIDLE ,&m_keepidle , sizeof optval );
	setsockopt(sockfd ,IPPROTO_TCP,TCP_KEEPINTVL ,&m_kintp , sizeof optval );
	for(;;){
	 	connfd =accept(sockfd  , nullptr , nullptr);
		if(connfd == -1){
			if((errno == EAGAIN) || (errno == EWOULDBLOCK) || (errno == EINPROGRESS)){
				std::fprintf(stderr , "ERRTIMEOUT connection was closed\n");
				break ;
			}else {
				std::fprintf(stderr , "I dont know what it is \n");
				break ;
			}
		}
		}
	close(sockfd);
return 0;	
}
