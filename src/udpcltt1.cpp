
#include <sys/socket.h>
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
	char sendline[MAX_LINE+1] , recline[MAX_LINE+1] ; 
	ssize_t n ;
	while(fgets(sendline ,MAX_LINE , stdin) != nullptr){
		if(sendto(sockfd , sendline , std::strlen(sendline) , 0 , reinterpret_cast<const struct sockaddr*>(&srvaddr) , sizeof srvaddr) == -1 ){
			continue; 
		}
		if((n = recvfrom(sockfd,recline, MAX_LINE, 0, nullptr , nullptr )) == -1 ){
			continue;
		}
		recline[n] = 0x00 ; 
		std::puts(recline);
	}
	return 0;
}
