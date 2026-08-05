
#include <cstring>
#include <sys/socket.h>
#include <unp.h>

using sockadr = struct sockaddr*;
int main(){
	int sockfd; 
	[[maybe_unused]] socklen_t len ; 
	struct sockaddr_un srvadr{};
	if((sockfd = socket(AF_LOCAL , SOCK_STREAM , 0)) < 0 ) {return -1;}
	srvadr.sun_family = AF_LOCAL ; 
	strcpy(srvadr.sun_path , "/tmp/jolly"); 
	if(bind(sockfd , reinterpret_cast<sockadr>(&srvadr), sizeof srvadr) == -1 )return -1;
}
