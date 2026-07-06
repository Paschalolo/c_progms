#include <arpa/inet.h>
#include <mysock.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>


int main(int argc , char** argv ){
	struct sockaddr_in mcastgrp = {0};
	struct in_addr localintf ; /* Ip address of lcoal interfaces */ 
	int sfd ; 
	char databuf[BUFLEN] ={0};
	unsigned char loopval ; 
	unsigned int ttlval ; 
	socklen_t ttlvalsz = sizeof(ttlval);
	char* localintfaddr = "255.0.0.0" ;

	if(argc > 1 ) {
		localintfaddr = argv[1];
	}

	/* Create a datagram socket*/ 
	sfd = socket(AF_INET , SOCK_DGRAM , 0); 
	if(sfd < 0 ){
		fprintf(stderr , "socket() failed\n");
	}
	mcastgrp.sin_addr.s_addr = inet_addr(localintfaddr);
	mcastgrp.sin_family = AF_INET ; 
	mcastgrp.sin_port = htons(9000);
	
	loopval = 1; 
	if(setsockopt(sfd , IPPROTO_IP ,IP_MULTICAST_LOOP ,(char*)&loopval, sizeof(loopval)) < 0){
		close(sfd);
		return -3;
	}
	return 0;
}
