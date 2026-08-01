/* This porject by Paschal Ahanmisi */
#include <netinet/in.h>
#include <sys/socket.h>
#include <unp.h>


int main(){
	int listenfd , connfd ; 
	pid_t childpid ; 
	socklen_t chilen {static_cast<socklen_t>(sizeof(struct sockaddr_in))};  
	My_sockaddr_in_t cliaddr{} , srvadr{AF_INET , htons(8080) ,htonl(INADDR_ANY) };
	if ((listenfd = socket(AF_INET , SOCK_STREAM , 0)) == -1 ){
		err_sys("socket()\n");
	}

	// bind 
	if(bind(listenfd  ,reinterpret_cast<const sockaddr*>(&srvadr.m_sockaddr), sizeof srvadr ) == -1 ){
		err_sys("bind () failed");
	}
	
	// lsiuten 
	if(listen(listenfd , BACK_LOG) == -1 ){
		err_sys("listen failed");
	}

	for(;;){
		connfd = accept(listenfd , reinterpret_cast<struct sockaddr*>(&cliaddr.m_sockaddr) ,&chilen);
		if(connfd == -1) {
			std::fprintf(stderr , "Connection failed\n");
			continue;
		}
		if((childpid = fork()) == 0 ){
			str_echo(connfd);
			close(connfd) ; 
			exit(0); 
		}else if (childpid == -1){
			err_sys("could not fork");
		}
	}
	close(listenfd);
	return 0;
}

