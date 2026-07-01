#ifndef MY_SOC 
#define MY_SOC
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


constexpr int BUFLEN = 1024 ; 
constexpr int DES_PORT = 2345 ;  
[[maybe_unused]] constexpr int MAXMSGS =3 ; 
#define IPV4LOCALADDR "127.0.0.0"


#endif
