

#include <sys/mman.h>
#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#define LEN (1024 * 1024 )

#define SHELL_FMT "cat /proc/%ld/maps | grep zero"

#define CMD_SIZE (sizeof(SHELL_FMT) + 20)


int main(){
	char cmd[CMD_SIZE] ; 
	char *addr ; 

	addr = reinterpret_cast<char*>(mmap(nullptr , LEN , PROT_NONE , MAP_SHARED | MAP_ANONYMOUS , -1 , 0));
	if(addr == MAP_FAILED) return -2;

	std::printf("Before mprotect\n");
	snprintf(cmd , CMD_SIZE , SHELL_FMT, (long)getpid());
	[[maybe_unused ]]int ret ; 
	ret = system(cmd) ;

	if(mprotect(addr, LEN , PROT_READ| PROT_WRITE) == -1 ) {return -3;}

	std::printf("After mprotect \n") ; 
	 ret =system(cmd);
	return 0 ;
}
