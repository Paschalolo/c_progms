


/* Get and set coket size for socket buffer 
 * Authored by Paschal Ahanmisi 
 */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netinet/tcp.h>

int main([[maybe_unused]]int argc , [[maybe_unused]]char** argv ){
	
	int ret ; 
	int sfd ; 
	int option ; 
	socklen_t optlen ; 

	/* create a stream socket */ 
	sfd = socket(AF_INET , SOCK_STREAM , 0);

	if(sfd < 0){
		fprintf(stderr , "socket() could not be opened ");
		return -1; 
	}
	
	/* Get original setting of the socket option */ 
	option = 0 ; 
	optlen = (int)sizeof(option) ; 
	ret = getsockopt(sfd,SOL_SOCKET , SO_SNDBUF, (void*)&option ,&optlen ); 
	if(ret == -1 ){
		fprintf(stderr , "Error getsocklen %d " , errno); 
		close(sfd);
		return -2;
	}
	printf("SOcket size is %d\n" , option);
	
	option = option+  2048 ; 
	ret = setsockopt(sfd, SOL_SOCKET,SO_SNDBUF,(void*)&option ,optlen ); 
	if(ret == -1 ){
		fprintf(stderr , "Error getsocklen %d " , errno); 
		close(sfd);
		return -2;
	}
	option = 0;
	ret = getsockopt(sfd,SOL_SOCKET , SO_SNDBUF, (void*)&option ,&optlen ); 
	if(ret == -1 ){
		fprintf(stderr , "Error getsocklen %d " , errno);
		close(sfd);
		return -2;
	}
	printf("New socket value %d ", option);

	close(sfd);
	return 0 ; 
}
