
/*
 *	A conectionless server program using datagram sockets 
 *	Usage : udpsrv $[port]
 *	Copyright (c) 2024 - 2026
 * */

#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

constexpr int BUFLEN = 1024 ; 
constexpr int DES_PORT = 2345 ; 


int main(int argc , char** argv ){
	ssize_t ret;
	int  portnum_in = 0 ; 
	int sfd ; 
	struct sockaddr_in srvaddr ;
	constexpr int srvaddr_lem = sizeof(struct sockaddr_in);
	struct sockaddr_in clntaddr ;  /* client ip adrr */
	constexpr 	socklen_t  clntaddr_sz = sizeof(struct sockaddr_in); /* client sock_in len */
	in_port_t portnum = DES_PORT ; /* Default port adress */ 

	char inbuf[BUFLEN] = {0} ;
	char outbuf[BUFLEN] = {0};
	size_t msg_len = 0;

	fprintf(stdout , "Connectionless server program ... \n");

	if(argc > 1) {
		portnum_in = atoi(argv[1]);
		if(portnum_in <= 0 ) {
			fprintf(stderr, "Port number %d invalid , set to default %d", portnum_in , portnum);
			portnum = DES_PORT ;
		}else{
			portnum= (in_port_t)portnum_in ;
		}
	}

	/* CReate the datagram server socket*/ 
	if((sfd = socket(AF_INET , SOCK_DGRAM , 0) ) < 0){
		fprintf(stderr, "Coulnot open server");
		return -1;
	}
	memset((void*)&srvaddr, 0X00,srvaddr_lem );
	srvaddr.sin_family = AF_INET ; 
	srvaddr.sin_port = portnum ;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);


	if((ret = bind(sfd , (const struct sockaddr*)&srvaddr, srvaddr_lem)) == -1){
		fprintf(stderr , "Couldnot bind the server \n"); 
		close(sfd);
	}
	/* Set a reply messaeg */ 
	sprintf(outbuf, "%s" , "This is a reply from the server program"); 
	msg_len = strlen(outbuf); 

	fprintf(stdout , "Listening at port number %u" , (unsigned)portnum);
	/* Recieve service requests from clients */ 
	while(true){
		errno = 0 ; 
		inbuf[0] = 0x00;
		ret = recvfrom(sfd,(void*)inbuf , (size_t)BUFLEN , 0 , (struct sockaddr* restrict )&clntaddr, ( socklen_t* restrict)&clntaddr_sz);
	/*Process the request */
		if(ret > 0){
		inbuf[ret] = 0x00 ; 
		printf("Received the following request from client : \n%s", inbuf); 


		/*send a reply */ 
		ret = sendto(sfd, (const void*)outbuf , msg_len , 0 , (const struct sockaddr*)&clntaddr, (socklen_t)clntaddr_sz);
		if(ret ==-1){
			fprintf(stderr , "failed to send back to client\n") ; 
		}else{
			printf("SENT %ld BYTES OUT OF %ld \n" , ret, msg_len );
		}
		}else if(ret < 0 ){
			fprintf(stderr , "Failed to receive nothing from client \n");;
		}else{
			printf("It might be possible that client is down\n");
		}
	}

	// Unnnecessary because code path is dead 
	close(sfd);
	return 0 ;
}
