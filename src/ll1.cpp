


#include <cerrno>
#include <cstdio>
#include <string.h>
#include <errno.h>
int main(){	
	std::printf("%s" , strerror(EADDRINUSE));
	return 0;
}
