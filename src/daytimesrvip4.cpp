/* tcp daytime servesr 
 */ 


#include <cstdio>
#include <sys/socket.h>
#include <unp.h>
#include <ctime>
#include <cstring>
#include <errno.h>
int main(){
	int listenfd , connfd ;
	struct sockaddr_in srvadr ; 
	char buff[MAX_LINE];
	time_t ticks ; 
	listenfd = socket(AF_INET ,SOCK_STREAM, 0);
	if(listenfd == -1 ){
		err_sys("Socket failed");
	}
	
	std::memset(reinterpret_cast<void*>(&srvadr), 0x00 , sizeof srvadr);
	srvadr.sin_family = AF_INET ; 
	srvadr.sin_port = htons(13);
	srvadr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if((bind(listenfd,reinterpret_cast<const struct sockaddr *>(&srvadr), static_cast<socklen_t>(sizeof srvadr))) == -1){
		std::fprintf(stderr, "%s" , strerror(errno));
		err_sys("bind error");
			}

	if(listen(listenfd , BACK_LOG) == -1 ) {
		err_sys("listen error ");
	}

	for(;; ){
		connfd = accept(listenfd , nullptr , nullptr);
		if(connfd == -1){
			std::printf("Server failed to accept packet\n");
			continue ;
		}
		ticks = time(nullptr) ;
		std::snprintf(buff,MAX_LINE,"%s %s \r\n" , ctime(&ticks) , "from Paschal Cloud\n");
		ssize_t rr1 =write(connfd ,buff , strlen(buff) );
		if(rr1 == -1){
			std::fprintf(stderr , "server failed to write to buffer \n");	
		}
		std::printf("Wrote %ld to client \n", rr1);
		close(connfd) ;
	}
	close(listenfd);
	return 0;
}
