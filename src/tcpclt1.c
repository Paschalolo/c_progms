/* A conwection oriented client progam of stream socket 
 * connecting to server in the smae local host or a different remote host 
 * Copyright (c) 2024 - 2026 
 * */ 

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
constexpr int DPORT = 2345 ;
constexpr int MAXMSGS = 3;
#define IPADDRESSLOCAL "127.0.0.0"
int main(int argc , char** argv){
	ssize_t rr ; 
	int ret , portnum_in = 0 ; 
	int sfd ; 
	struct sockaddr_in server ; 
	constexpr socklen_t serversz  = sizeof(struct sockaddr_in);
	struct sockaddr_in fromadrr ; 
	socklen_t fromaddrsz = sizeof(struct sockaddr_in);

	in_port_t portnum = DPORT ; 
	char inbuf[BUFLEN]= {0} ; 
	char outbuf[BUFLEN] = {0} ;

	size_t msglen = 0 ; 
	size_t msgnum = 0 ; 

	char* ipaddrstr = IPADDRESSLOCAL ; 
	in_port_t ipaddrbin ; 
	printf("Connection oriented cleint program ... \n");

	if (argc > 1 ) {
		portnum_in = atoi(argv[1]); 
		if(portnum_in <= 0 ){
			fprintf(stderr , "Port is wrong %u", (unsigned) portnum_in);
			portnum = (in_port_t)DPORT ; 
		}else {
			portnum = (in_port_t)portnum_in ; 
		}

	}

	if(argc > 2 ) {
		ipaddrstr = argv[2] ; 

	}
	
	
	ret = inet_pton(AF_INET , ipaddrstr , (void*)&ipaddrbin);
	if(ret == 0 ) {
		fprintf(stderr , "not a valid ipaddress \n");
	}


	/* create client socket */ 
	sfd = socket(AF_INET , SOCK_STREAM , 0 );
	if(sfd ==-1 ) {
		fprintf(stderr , "could not fail socket()");
		return -2 ; 
	}

	memset((void*)&server, 0,serversz);
	server.sin_addr.s_addr = ipaddrbin;
	server.sin_port = htons(portnum) ; 

	server.sin_family = AF_INET ;

	ret = connect(sfd , (const struct sockaddr* )&server , serversz);
	if(ret == -1 ){
		fprintf(stderr , "Error connect()") ;
	return -3 ; 
	}
	printf("Sebd request messages to server %s at port %d\n", ipaddrstr, portnum);

	while(msgnum < MAXMSGS) {
		sprintf(outbuf , "%s %lu", "This messafe is from client program", msgnum++);
		msglen = strlen(outbuf); 

		rr = send(sfd , (void*)outbuf , msglen , 0);
		if(rr >= 0 ) {
		/* receive a request from server */ 
			inbuf[0] = 0x00 ; 

			rr = recv(sfd, inbuf,BUFLEN , 0); 
			if(ret > 0){
				inbuf[ret] = 0x00 ; 
				printf("Received this message fromserver %s\n",inbuf );
			}else if(ret == 0 ){
				fprintf(stderr , "Warning zero bytes received \n");
			}else {
				fprintf(stderr , "Call failed\n");	
			}
		}else {
			fprintf(stderr , "send failed()\n");
			break ; 
			}
	}
	close(sfd);
	return 0;
}

