
#ifndef  UNP_H 
#define UNP_H 
#include <cerrno>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <sys/utsname.h>
#include <cstring>
#include <sys/un.h>
#include <arpa/inet.h>
#include <time.h>
#include <poll.h>
constexpr size_t MAX_LINE = 1024 ; 
constexpr size_t BACK_LOG = 4096;

struct Binar_t {
	long m_ab_; 
	long g_; 
};
struct My_sockaddr_in_t {
	My_sockaddr_in_t(sa_family_t  family , in_port_t port  ,in_addr_t addr) noexcept {
			m_sockaddr.sin_family = family ; 
			m_sockaddr.sin_port = port ;
			m_sockaddr.sin_addr.s_addr = addr ; 
	}
	My_sockaddr_in_t() = default;
	My_sockaddr_in_t(const My_sockaddr_in_t&) = delete ; 
	My_sockaddr_in_t( My_sockaddr_in_t&&) = delete ; 
	My_sockaddr_in_t& operator=( My_sockaddr_in_t&&) = delete ; 
	My_sockaddr_in_t& operator=( const My_sockaddr_in_t&) = delete ; 
	struct sockaddr_in m_sockaddr{} ;
};
void err_quit(const char* __restrict__ str ){
	std::fprintf(stderr , "%s", str);
	exit(EXIT_FAILURE); 
}

void err_sys(const char* __restrict__ str){
	std::fprintf(stderr , "%s", str);
	exit(EXIT_FAILURE); 
}

__attribute__((always_inline)) static inline int Socket(int family , int type , int protocol){
	int n ; 
	if((n= socket(family , type , protocol)) == -1 ){
		err_sys("socekt failed");
	}
	return n;
}

void str_echo(int fd){
	ssize_t n ; 
	char buf[MAX_LINE] ; 
	while ((n = read(fd , buf  , MAX_LINE)) >= 0 ){
		if((n == 0) && (errno == EINTR)){
			continue;
		}else {
			return ;
		}
		[[maybe_unused]] ssize_t ret = write(fd , buf , static_cast<size_t>(n) )  ; 
	}
	if(n == -1){
		err_sys("read() failed\n");
	}
}

#endif 

