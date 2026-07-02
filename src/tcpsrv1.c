/* A connection oriented server program using stream sockers
 *	Single threaded server 
 *	Authored by Paschal Ahanmisi 
 *	Copyright (c) 2024 - 2026
 * */

#include <stddef.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

constexpr int BUFLEN = 1024 ; 
constexpr int DES_PORT = 2345 ; 
constexpr int BACKLOG = 50 ; /* length of the listiner queue */

int main(int argc , char** argv){
	ssize_t rr;
		int ret , portnum_in = 0 ; 
		int sfd ; /* file descriptor of the listiner socket */
		int newsock; /* The file descriptor of client data socket */
		struct sockaddr_in srvaddr ;
		constexpr size_t srvaddrsz= sizeof(struct sockaddr_in);
		struct sockaddr_in clientaddr ;
		socklen_t clientaddrsz = sizeof(struct sockaddr_in) ;

		in_port_t portnum = (in_port_t)DES_PORT ; 
		char inbuf[BUFLEN] = {0} ; 
		char outbuf[BUFLEN] = {0};
		size_t msglen ; 
		unsigned int msgcnt ;

		printf("Connection Oriented Server \n");

		if(argc >1) {
			portnum_in = atoi(argv[1]); 
			if(portnum_in <= 0 ) {
				fprintf(stderr , "Port number is invalid %d ", portnum_in);
				portnum = (in_port_t)DES_PORT ; 
			}else {
				
				portnum = (in_port_t)DES_PORT ; 
			}

			/* Create a server stream socket*/ 
			sfd = socket(AF_INET , SOCK_STREAM , 0); 
			if(sfd == -1) {
				fprintf(stderr , "couldnot create  a socket\n");
				return -1; 
			}
			memset((void*)&srvaddr , 0x00 , srvaddrsz); 
			srvaddr.sin_port = htons(portnum);
			srvaddr.sin_family = AF_INET ;
			srvaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
			/* Bind the server socket to the address */
			ret = bind(sfd ,(const struct sockaddr*)&srvaddr , (socklen_t)srvaddrsz );
			if(ret == -1 ){
				fprintf(stderr , "Couldnto bind the server \n");
				return -1; 
			}

			/* Ste amximu number of conntion request queue*/ 
			if(listen(sfd, BACKLOG) == -1){
				fprintf(stderr , "COuld not call listen\n"); 
				return -4;
			}


		}

		while(1){
			printf("Listening at port number %u", portnum);
			newsock = accept(sfd, (struct sockaddr *restrict)&clientaddr, (socklen_t *)&clientaddrsz);
			if(newsock == -1) {
				fprintf(stderr , "accept failed");
				return -4; 
			}
			printf("CLient connected\n");
			msgcnt = 1;
			errno = 0 ; 
			while(1){
				errno = 0 ; 
				inbuf[0] = 0x00 ; 
				rr = recv(newsock , (void*)inbuf , BUFLEN , 0); 
				if(rr == -1 ){
					
				}else if (rr > 0){
					inbuf[ret] = 0x00 ; 
					printf("Receiuved the following request : %s ", inbuf);

					/* construct a repply */ 
					sprintf(outbuf , "this is a reply from the server program %d", msgcnt++); 
					msglen = strlen(outbuf); 
					rr = send(newsock ,(void*)&outbuf , msglen , 0 );
					if(rr == -1 ){
						fprintf(stderr , "Error occured in send \n" );
					}else {
						printf("sent %lu bytes to the reply sent\n" , rr);
					}
				}else if (rr < 0 ){
					printf("client might have disconnected");
					break;
				}else {
					fprintf(stderr , "Error recv() failed");
					break ;
				}
			close(newsock);
			}

		}

		close(sfd);
		return 0;
}
