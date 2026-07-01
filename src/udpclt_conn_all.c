
/* A connectionless client program using conncet with datagrams sockets 
 *	Usage >> 
 *	Authored by Mr Paschal Ahanmisi
 * */

#include <errno.h>
#include <mysock.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

int main(int argc , char** argv ){
	ssize_t ret ;
	int rr ;
	int portnum_in = 0 ; 
	int sfd ; 
	struct sockaddr_in srvaddr ; 
	constexpr size_t  srvaddrsz = sizeof(struct sockaddr_in); 

	struct sockaddr_in fromaddr ; 
	constexpr socklen_t fromaddrsz = sizeof(struct sockaddr_in);
	in_port_t portnum = DES_PORT ; 
	char inbuf[BUFLEN] = {0};
	char outbuf[BUFLEN] = {0} ; 
	
	size_t msglen = 0 ; 
	size_t msgnum = 0 ; 
	char* ipaddstr  =IPV4LOCALADDR ; 
	in_addr_t ipaddrbin  ; 
	
   fprintf(stdout , "Conectionless client program\n");

	if(argc > 1 ) {
		portnum_in = atoi(argv[1]); 
		if(portnum_in <= 0 ) {
			fprintf(stderr , "Port number %d is invalid\n" , portnum_in); 
		}else {
			portnum = (in_port_t)portnum_in ; 
		}
	}

	if(argc > 2 ) {
		ipaddstr = argv[2] ;
		// Convert string to binary 
		 rr = inet_pton(AF_INET , ipaddstr , (void*restrict)&ipaddrbin);
		 if(rr == 0){
			fprintf(stderr , "Error converting the bin address ");
		 }

	}


	/* Create a socket client */ 
	if((sfd = socket(AF_INET, SOCK_DGRAM , 0 )) == -1){
		fprintf(stderr , "Could not connect to socket\n");
		return -2 ;
	}
	
	/* Fill in the server address */ 
	memset((void*)&srvaddr , 0x00 , srvaddrsz);
	srvaddr.sin_family = AF_INET ; 
	srvaddr.sin_port = htons(portnum);
	if(ipaddrbin){
		srvaddr.sin_addr.s_addr = htonl(ipaddrbin);
	}else{
		srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}

	/*fix our target peer address */ 
	rr = connect(sfd,( const struct sockaddr *)&srvaddr,(socklen_t)srvaddrsz);
	if(rr == -1){
		fprintf(stderr, "connect failed ") ;
		close(sfd) ; 
		return -4;
	}
	
	printf("Sending request to the server ");
	while (msgnum < MAXMSGS) {
		sprintf(outbuf , "%s" , "This is the request message \n"); 
		msgnum++;
		msglen = strlen(outbuf);
	errno = 0 ;
	ret = sendto(sfd,(const void*) outbuf , msglen , 0 , (const struct sockaddr*)NULL , 0 );

	if(ret >= 0 ) {
		printf("\n %lu bytes writen of messages where written ", ret);
		if (ret > 0) {
			/* Get server reply */ 
			inbuf[0] = 0x00 ;
			ret = recvfrom(sfd , (void* restrict )inbuf , BUFLEN);
	
		}
	}
	return 0; 
}
