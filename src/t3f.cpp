
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <apie.h>
#include <cstring>
constexpr char buf1[] = "abcdefjhij" ;
constexpr char buf2[] = "ABCDEFGHIJ" ;

int main(){
	int fd ; 
	if((fd = open("./file.hole", O_WRONLY |O_CREAT , S_IRWXU)) == -1){err_sys("openerror");}
	const  size_t sz = std::strlen(buf1);
	if(write(fd , buf1 , sz) != (ssize_t)sz){
		err_sys("write() failed");
	}
	/* offset noew = sz */ 
	if(lseek(fd ,1634 , SEEK_SET ) == -1){err_sys("lseek failed");}

	if(write(fd , buf1 , sz) != (ssize_t)sz){
		err_sys("write() failed");
	}
	return 0;
}
