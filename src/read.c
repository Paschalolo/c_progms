

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFSZ 30 
#define READER_WAIT_TIME 1 
#define LOOPCNT 5


int main(int argc , char** argv ){
	char* fname = NULL ; 
	int fd ; 
	ssize_t bytes ; 
	char buf[BUFSZ];

	/* Expect to get the file name from the user */
	if(argc > 1  ) {
		fname = argv[1] ; 
	}else {
		fprintf(stderr,"Usage : %s filename \n", argv[0]);
		return -1;
	}
	
	/*Open the file for read only*/ 
	fd = open(fname ,O_RDONLY , (S_IWUSR | S_IRUSR));
	if(fd == -1 ) {
		fprintf(stderr , "Open() failed ");
		return -2; 
	}

	/* Read from the file */ 
	bytes = read(fd,buf ,BUFSZ  ); 
	if(bytes == -1 ) {
		fprintf(stderr , "Faield to read from file");
		close(fd) ; 
		return -3;
	}

	buf[bytes] = 0x00; /* set the last bytes to /0 */
	printf("just read the following %ld bytes from teh file %s : \n %s\n" , bytes , fname , buf);

	close(fd) ; 
	return 0;
}
