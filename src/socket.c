/*
*	socket()
*	Diffrent combinations of socket types and protocols that are supported 
*	Authored by Mr Paschal Ahanmisi Copyright (c) 2024 - 2026
*	All rights are reserved 
 * *
 *
 */

#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

__attribute__((cold, noinline)) int end_all(int val, const char* __restrict__ buf ){
	fprintf(stderr , "%s", buf); 
	return val; 
}

int main(){
	int sockfd ; 
	sockfd = socket(AF_INET , SOCK_STREAM , 0);
	if(sockfd == -1) {
		return end_all(-1, "socket(AF_INET , SOCK_STREAM , 0)")	;
	}else{
		printf(" IPV$ is supported \n");
		close(sockfd);

	}
	sockfd = socket(AF_INET, SOCK_DGRAM,0); 
	if(sockfd == -1 ) {
		end_all(-1, "socket afinet is not supported \n");
	}else{
		printf("socket datagrams connectionaless exists\n");
		close(sockfd);
	}

	sockfd = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
	if(sockfd == -1) {
		end_all(-1, "IP prootcol tcp doesn not exist \n");
	}else{
		printf("ipprotocol tcp exist");
		close(sockfd);
	}
	return 0;
}
