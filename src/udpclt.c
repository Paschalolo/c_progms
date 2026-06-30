
/*
 *	A conectionless client program using datagram sockets 
 *	Usage : udpclt $[port]
 *	Copyright (c) 2024 - 2026
 * */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

constexpr int BUFLEN = 1024 ; 
constexpr int DES_PORT = 2345 ; 
[[maybe_unused]] constexpr int MAXMSGS =3 ; 
#define IPV4LOCALADDR "127.0.0.0"



int main(int argc , char** argv ){
	ssize_t ret;
	int  portnum_in = 0 ; 
	int sfd ; 
	struct sockaddr_in srvaddr ;
	constexpr int srvaddr_lem = sizeof(struct sockaddr_in);
	struct sockaddr_in fromaddr ;  
	constexpr 	socklen_t  fromaddr_sz = sizeof(struct sockaddr_in); /* client sock_in len */
	in_port_t portnum = DES_PORT ; /* Default port adress */ 

	char inbuf[BUFLEN] = {0} ;
	char outbuf[BUFLEN] = {0};
	size_t msg_len = 0;
	size_t msgnum = 0 ; 
	char* ipaddstr = IPV4LOCALADDR ;
	in_addr_t ipaddbin ; 


	fprintf(stdout , "Connectionless client program ... \n");

	if(argc > 1) {
		portnum_in = atoi(argv[1]);
		if(portnum_in <= 0 ) {
			fprintf(stderr, "Port number %d invalid , set to default %d", portnum_in , portnum);
			portnum = DES_PORT ;
		}else{
			portnum= (in_port_t)portnum_in ;
		}
	}
	if(argc > 2 ) ipaddstr = argv[2];
	/* CReate the datagram client socket*/
	[[maybe_unused]]int r = inet_pton(AF_INET , ipaddstr, (void* restrict )&ipaddbin);

	if((sfd = socket(AF_INET , SOCK_DGRAM , 0) ) < 0){
		fprintf(stderr, "Coulnot open server");
		return -1;
	}
	memset((void*)&srvaddr, 0X00,srvaddr_lem );
	srvaddr.sin_family = AF_INET ; 
	srvaddr.sin_port = htons(portnum) ;
	if(ipaddbin){

		srvaddr.sin_addr.s_addr = ipaddbin;
	}else {
		srvaddr.sin_addr.s_addr = htons(INADDR_ANY);
	}


	if((ret = bind(sfd , (const struct sockaddr*)&srvaddr, srvaddr_lem)) == -1){
		fprintf(stderr , "Couldnot bind the server \n"); 
		close(sfd);
	}
	/* Set a reply messaeg */ 

	fprintf(stdout , "Send request messages to server (%s)at port %u \n",ipaddstr, (unsigned)portnum);
	/* Recieve service requests from clients */ 
	while(true){
		sprintf(outbuf,"This is request message %ld" , ++msgnum);
		msg_len = strlen(outbuf);
		outbuf[msg_len] = 0x00;
		ret = sendto(sfd, (const void*)outbuf, (size_t)msg_len , 0 , (const struct sockaddr*)&srvaddr,(socklen_t)srvaddr_lem);
		if(ret >= 0 ) {
			if((size_t)ret == msg_len){
				printf("bytes where succesfully sent\n");
			}else if((size_t)ret < msg_len){
				printf("some package frames are missing\n");
			}
			inbuf[0] = 0x00 ; 
			ret = recvfrom(sfd,(void*)inbuf , BUFLEN , 0 , (struct sockaddr*restrict)&fromaddr , (socklen_t*restrict)&fromaddr_sz ); 
			if(ret== 0 ){
				printf("zero bytes where received");
				}
		}
	
	}

	// Unnnecessary because code path is dead 
	close(sfd);
	return 0 ;
}
