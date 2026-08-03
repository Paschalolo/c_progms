

#include <sys/socket.h>
#include <unp.h>
#include <netdb.h>
#include <sys/types.h>

#include <arpa/inet.h>
int main(){
	struct addrinfo hints {}; 
	struct addrinfo *res ; 
	hints.ai_family = AF_UNSPEC ; 
	hints.ai_socktype = 0  ; 
	if (getaddrinfo("google.com", "https", &hints, &res) != 0 ) {
		err_sys("Failed lookup");
	}
	auto r_ptr = res ; 
	char dst[INET6_ADDRSTRLEN]{0};
	while(r_ptr != nullptr){
		std::printf("%s\n" , inet_ntop(r_ptr->ai_family ,reinterpret_cast<void*>(r_ptr->ai_addr) ,dst , r_ptr->ai_addrlen  ));
	r_ptr = r_ptr->ai_next;
	}

	freeaddrinfo(res);

}
