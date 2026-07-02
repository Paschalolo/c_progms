/*
 *	A connectionoroietned sever program using sock_stream 
 *	Support for ipv6 and ipv4 . Default to ipv6 . compile with -DIPV4 to make ipv4 
 *	Authored by Paschal Ahanmisi
 * */

#include <arpa/inet.h>
#include <mysock.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc , char** argv) {
	int ret ;
	ssize_t rr ; 
	int newsock ; 
	int sfd ; 

#if IPV4
	struct sockaddr_in servaddr ; 
	socklen_t srvaddrsz  = sizeof(struct sockaddr_in);
	struct sockaddr_in clientaddr ; 
	socklen_t clientaddrsz  = sizeof(struct sockaddr_in);
#else
	struct sockaddr_in6 servaddr = {0}; 
	socklen_t srvaddrsz  = sizeof(struct sockaddr_in6);
	struct sockaddr_in6 clientaddr = {0} ; 
	socklen_t clientaddrsz  = sizeof(struct sockaddr_in6);
	int v6only = 6;
#endif

	in_port_t portnum = DES_PORT ; 
	int port_num_in = 0 ; 
	char inbuf[BUFLEN] = {0}; 
	char outbuf[BUFLEN] = {0};
	size_t msglen ; 
	unsigned int msgcnt  = 0 ; 
	struct sockaddr_in6 peeradr6 = {0} ; 
	socklen_t peeraddr6_sz = sizeof(struct sockaddr_in6);
	

	fprintf(stdout , "Connection oriented sever porgram \n");
	if(argc > 1 ) {
		port_num_in = atoi(argv[1]); 
		if(port_num_in > 0 ) {
			portnum = (in_port_t) port_num_in ; 
		}else{
			fprintf(stderr , "Wrong port numebr given in this equation\n");
		}
	}

	/* Create a socket stream server */ 
	if((sfd = socket(AF_INET6 , SOCK_STREAM , 0)) == -1){
	fprintf(stderr, "Socket() failed\n");
	return -2 ;
	}

#if IPV4
	servaddr.sin6_addr = htonl(INADDR_ANY) ; 
	servaddr.sin6_port = htons(portnum); 
	servaddr.sin6_family = AF_INET;
#else 
	servaddr.sin6_addr = in6addr_any ; 
	servaddr.sin6_port = htons(portnum); 
	servaddr.sin6_family = AF_INET6;
#endif
	/* Bind the server */ 
	if((ret = bind(sfd , (const struct sockaddr*)&servaddr, srvaddrsz)) != 0 ){
		fprintf(stderr , "Error bind()\n");
		close(sfd);
		return -3; 
	}

	if((ret = listen(sfd , BACKLOG)) == -1){
		fprintf(stderr , "listen() failed ");
		close(sfd);
		return -4;
	}

	// Wait for incoming request from clients 
	while (1){} {
		printf("Listening on port %u" , portnum) ;
		newsock = accept(sfd, (struct sockaddr *restrict)&clientaddr, (socklen_t *restrict)&clientaddrsz);
		if(newsock < 0 ) {
			fprintf(stderr , "Error accept Failed");
			close(sfd);
			return -6;
		}
		inet_ntop(AF_INET6, (const void *restrict)&(clientaddr.sin6_addr),( char *restrict)&peeradr6,peeraddr6_sz);
		/* GEt pair ip address */ 

	}
	return 0 ; 
}
