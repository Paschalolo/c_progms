/*
 *	invlude File for projects 
 * */
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
#include <ctype.h>
#include <stdlib.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/un.h>

constexpr int BUFLEN = 1024 ; 
constexpr int BUFLEN1 = 1024 ; 
constexpr int DES_PORT = 2345 ;  
[[maybe_unused]] constexpr int MAXMSGS =3 ;
#define DEFSTRVPORT = "2345";
#define IPV4LOCALADDR "127.0.0.0"
#define NAMELEN 63 
#define BACKLOG 50 
#define IPADDRSZ 128 /* size of 128 bit ipv6 addr */ 
#define MAXSOURCES 5 
#define SLEEPS 3 
#define PEERADDRLEN 64 
#define SRVIPLEN 64 
#define MAXCOONNTRYCNT 5 
#define NET_DB_MAX_HOST_NAME_LENGTH 256 
#define SERVERNAME "localhost"
#define NO_HOST ""
#define IPV6LOCALADDR "::1"




#endif
