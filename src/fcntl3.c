

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc , char** argv){
	int flags , ret ; 
	int fd ; 
	char* fname = NULL ; 

	if(argc > 1) {
		fname = argv[1] ; 
	}else{
		return -2;
	}

	fd = open(fname , O_RDONLY , S_IRWXU);
	if(fd == -1 ) {
		return -3; 
	}

	flags = fcntl(fd , F_GETFD);
      	if(flags == -1){
		return -4;
	}
	printf("File descriptors flags oX%X\n", flags);

	/*Get status f;ags */
	flags = fcntl(fd,F_GETFL );
	if(flags == -1) {return -4;}
	printf("Access modes is 0x%x", flags);


	return 0 ; 
}
