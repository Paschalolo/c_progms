
#ifndef  UNP_H 
#define UNP_H 
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdlib> 
constexpr size_t MAX_LINE = 1024 ; 
constexpr size_t BACK_LOG = 100;

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
#endif 

