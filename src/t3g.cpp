#include <apie.h>
#include <unistd.h>
#include <fcntl.h>



int main(int argc , char** argv) {
	int val ;
	int fd ; 
	if(argc != 2 ) {return -2;}
	fd = open(argv[1] , O_RDONLY , S_IRWXU);
	if((val = fcntl(fd , F_GETFL)) < 0 )return -2;
	return 0;
}
