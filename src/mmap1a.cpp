
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err_tlp_v1.h>
int main( int argc , char** argv){
	char* addr ; 
	int fd ; 
	struct stat sb ={} ; 

	if(argc < 2 ) {errMsg("Not enough args\n" , ERRMSG_NOSET , -1);}
	fd = open(argv[1] , O_RDONLY ,  S_IRWXU );	
	if(fd ==-1) errMsg("Error open failed() \n" , ERRMSG_NOSET , -1); 

	if(fstat(fd , &sb) == -1 )exit(-1); 
	addr = reinterpret_cast<char*>(mmap(nullptr , static_cast<size_t>(sb.st_size) , PROT_READ| PROT_WRITE , MAP_PRIVATE , fd , 0));	
	if(addr == MAP_FAILED) errMsg("Mmap failed\n", ERRMSG_NOSET , -1);

	ssize_t sz = write(STDOUT_FILENO , addr , static_cast<size_t>(sb.st_size));
	if(sz == -1 ) return -1;
	return 0 ;
}
