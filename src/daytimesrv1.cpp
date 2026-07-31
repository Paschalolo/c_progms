

#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unp.h>


int main(){
	int listenfd , connfd ; 
	socklen_t len  = sizeof(struct sockaddr_in); 
	struct sockaddr_in srvadr , clntaddr ; 
	char buf[MAX_LINE] ;
	time_t ticks;
	ssize_t ret ;
	/* Make socket connection */ 
	if((listenfd = socket(AF_INET , SOCK_STREAM ,0 )) == -1){
		err_sys("socket() failed\n");
	}
	
	std::memset(reinterpret_cast<void*>(&srvadr), 0x00 , sizeof srvadr);
	/*bind connection */
	srvadr.sin_addr.s_addr = INADDR_ANY ; 
	srvadr.sin_port = htons(8080);
	srvadr.sin_family = AF_INET ;
	if(bind(listenfd , reinterpret_cast<const struct sockaddr *>(&srvadr), sizeof srvadr) == -1 ){
		err_sys("bind() failed\n"); 
	}

	if(listen(listenfd , BACK_LOG)== -1){
		err_sys("Listening failed");
	}

	for(;;){
		connfd = connect(listenfd ,reinterpret_cast<const struct sockaddr*>(&clntaddr), len );
		std::printf("connection from %s on port : %d\n" , inet_ntop(AF_INET , reinterpret_cast<const void*>(&clntaddr),buf , sizeof clntaddr) , static_cast<int>(ntohs(clntaddr.sin_port)));

		ticks =time(nullptr);
		snprintf(buf, MAX_LINE ,"%.24s \n" , ctime(&ticks));
		ret = write(connfd , buf , std::strlen(buf));
		if(ret == -1 ){
			std::fprintf(stderr , "Write code failed");
			continue ;
		}
		close(connfd);
	}
	/* lisening to the port */
	close(listenfd);
	return 0;
}
