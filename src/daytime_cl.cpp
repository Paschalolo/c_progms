/* CLient day time server */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <unp.h>
#include <cstring>

int main(int argc , char** argv){
	int sockfd ;
	ssize_t n ; 
	char recvline[MAX_LINE];
	struct sockaddr_in  servaddr ; 
	if(argc != 2 ) {
	err_quit("usage a.out <IPADDRESS>");	
	}

	if((sockfd = socket(AF_INET , SOCK_STREAM ,0 ))== -1 ){
		err_sys("socket error ");
	}
	std::memset(reinterpret_cast<void*>(&servaddr), 0x00 , sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET ; 
	servaddr.sin_port =  htons(13); /* Daytime server */ 
	if(!inet_pton(AF_INET, argv[1] , static_cast<void*>(&(servaddr.sin_addr.s_addr)))){
	err_sys("converting steing to IP failed");	
	}

	if(connect(sockfd , reinterpret_cast<const struct sockaddr*>(&servaddr),static_cast<socklen_t>(sizeof servaddr) ) == -1 ){
		err_sys("connect error");
	}

	while((n = read(sockfd , recvline , MAX_LINE)) > 0 ){
		recvline[n] = 0x00 ;
		ssize_t rr = write(STDOUT_FILENO ,recvline, static_cast<size_t>(n));
		if(rr == -1){
			err_sys("Failed to write to stdout");
		}
	}
	if(n == -1 ) {
		err_sys("read error ");
	}
	close(sockfd);
	return 0;
}
