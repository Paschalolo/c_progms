
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


void err_quit(const char* __restrict__ str ){
	std::fprintf(stderr , "%s", str);
	exit(EXIT_FAILURE); 
}

void err_sys(const char* __restrict__ str){
	std::fprintf(stderr , "%s", str);
	exit(EXIT_FAILURE); 
}
#endif 

