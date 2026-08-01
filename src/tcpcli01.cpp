
#include <netinet/in.h>
#include <sys/socket.h>
#include <unp.h>

void str_cli(int fd );

int main(int argc , char** argv ){
	int sockfd ; 
	struct sockaddr_in srvaddr ; 
	if(argc < 2 ){
		err_sys("./bin/<exceutable > name of address ");
	}

	if((sockfd = socket(AF_INET , SOCK_STREAM, 0))  == -1){
		err_sys("sockert() failed");
	}
	srvaddr.sin_port = htons(8080) ; 
	srvaddr.sin_family = AF_INET ; 
	if( inet_pton(AF_INET ,argv[1] , reinterpret_cast<void*>(&(srvaddr.sin_addr))) != 1){
		err_sys("inet_pton \n" );
	}

	if(connect(sockfd , reinterpret_cast<const struct sockaddr*>(&srvaddr) , static_cast<socklen_t>(sizeof srvaddr)) == -1)		{
		err_sys("connection failed() ");
	}
	str_cli(sockfd);
	close(sockfd);
}

void str_cli(int fd){ 
	char  sendbuf[MAX_LINE] ;
	[[maybe_unused]]ssize_t n ; 
	while((n = read(0 ,sendbuf , 20 ))) {
		auto sz = std::strlen(sendbuf);
		n = write(fd , sendbuf ,sz );
	}
}
