

#include <fcntl.h>

int main(){
	if (flags = fcntl(fd , F_GETFL, 0) < 0 ){return -1 ; }
	flags |= O_NONBLOCK ; 
	fcntl(fd,F_SETFL, flags);
}
