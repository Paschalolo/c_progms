#include <unistd.h>
#include <cstdio>



int main(){
	std::printf("uid = %d , gid = %d\n", getuid() , getgid());
	return 0;
}
