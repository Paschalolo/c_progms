
#include <netinet/in.h>
#include <sys/socket.h>
#include <unp.h>


int main(int argc , char** argv ){
	int sockfd ; 
	struct sockaddr_in srvaddr ; 
	if(argc < 2 ){
		err_sys("./bin/<exceutable > name of address ");
	}

	if((sockfd = socket(AF_INET , SOCK_STREAM, 0))  == -1){
		err_sys("sockert() failed");
	}
	srvaddr.sin_port = htons(8080) ; 
	srvaddr.sin_family = AF_INET ; 
	if( inet_pton(AF_INET ,argv[1] , reinterpret_cast<void*>(&(srvaddr.sin_addr))) != 1){
		err_sys("inet_pton \n" );
	}

	if(connect(sockfd , reinterpret_cast<const struct sockaddr*>(&srvaddr) , static_cast<socklen_t>(sizeof srvaddr)) == -1)		{
		err_sys("connection failed() ");
	}

	char bb[sizeof(Binar_t)];
	if(read(sockfd , bb , sizeof(Binar_t) ) < 1){
		std::fprintf(stderr ,"Could not read binary struct from file\n");
	}

	std::printf("struct binary Binar_t a: %ld , %ld ", reinterpret_cast<Binar_t*>(bb)->m_ab_ ,reinterpret_cast<Binar_t*>(bb)->g_ );
	close(sockfd); 

	return 0;
}
