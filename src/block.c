#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	struct stat st = {0} ; 
	int fd ; 
	fd = open("./bin/test", O_RDONLY , S_IRWXU);

	if(fd == -1){
		return -1; 
	}
	fstat(fd , &st) ;
	printf("Block_size : %ld \n" , st.st_blksize);
	printf("Block_size : %ld \n" , st.st_blocks);
	close(fd) ; 
}
