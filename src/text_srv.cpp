

#include <cstring>
#include <cstdio>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
 #include <arpa/inet.h>

constexpr int BACKLOG = 100;
int main(){
	struct sockaddr_in srvadr; 
	int sockfd ;
	int clientfd ;
	constexpr char buf[] = "This is simply a text file\nHello hope you have heared";
	const size_t sz = std::strlen(buf);
	ssize_t r1 ; 
	
	if ((sockfd = socket(AF_INET , SOCK_STREAM , 0)) == -1 ){
		fprintf(stderr , "Could not connect to socket()");
		return -1;
	}
	std::memset(reinterpret_cast<void*>(&srvadr) , 0x00 , sizeof(struct sockaddr_in));
	srvadr.sin_family = AF_INET ; 
	srvadr.sin_port = htons(8080);
	srvadr.sin_addr.s_addr = INADDR_ANY;
	// Bind the address now to the socket
	if(bind(sockfd , reinterpret_cast<const struct sockaddr*>(&srvadr) , sizeof(struct sockaddr_in)) == -1){
		std::fprintf(stderr ,"Sevrer bind() failed ");
		return -1;
	}

	// listening on port 
	if(listen(sockfd,BACKLOG) == -1){
		std::fprintf(stderr , "Listen() failed ");
		return -1;
	}

	std::printf("Listeinng on port 8080 on all ports \n");
	
	for(;;){
		clientfd = accept(sockfd, nullptr , nullptr);
		if(clientfd == -1) {
			std::fprintf(stderr , "Failed to make connection with server\n");
			continue;
		}
		r1 = write(clientfd , buf ,sz );
		std::printf("Written %ld bytes to client /n" , r1);
		close(clientfd) ; 
	}
	close(sockfd);
}
