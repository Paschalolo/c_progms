


#include "err_tlp_v1.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
constexpr size_t MEM_SIZE {10};
int main(int argc , char ** argv ) {
	char* addr ; 
	int fd ;
	if (argc  < 3 ) {errMsg("no args \n" , ERRMSG_NOSET , -1);}
	
	fd = open(argv[1] , O_RDWR, S_IRUSR);
	if(fd == -1 ) exit(-1);

	addr = reinterpret_cast<char*>(mmap(nullptr , MEM_SIZE , PROT_READ | PROT_WRITE , MAP_SHARED , fd , 0));
	if(addr == MAP_FAILED) { close(fd) ;exit(-1);} 
	if(close(fd ) == -1 ) exit(1);
	addr[MEM_SIZE -1 ] = 0x00 ; 
	std::printf("Current string = %s\n" ,  addr);

	std::strncpy(addr , argv[2] , MEM_SIZE- 1 );

	if(msync(addr , MEM_SIZE , MS_SYNC)== -1) errMsg("msync failed " , ERRMSG_NOSET , -1);
	std::printf("Printed to shared memory\n");
	munmap(addr , MEM_SIZE);
	return 0 ;
}
