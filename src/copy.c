
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 2048

int main(int argc , char** argv){
	char* infname , *outfname ;/* names of the input and output file name */ 
	int infd , outfd ; /* names of the input and output file descriptor */ 
	int ret = 0 ; 
	ssize_t bytes_rd , bytes_wr ; 
	size_t count ; 
	int done = 0 ; 
	char buf[BUFSZ] ; 
	char* bufadr;


	if(argc > 2 ) {
		infname = argv[1] ; 
		outfname = argv[2] ; 
	}else {
		fprintf(stderr , "Usage %s filename inputfile output_file\n", argv[0]);
		return -1; 
	}

	/* Open the input file for read only */ 
	infd = open(infname , O_RDONLY , S_IRUSR | S_IWUSR);
	if(infd == -1) {fprintf(stderr, "opening file failes"); return -2; }
	/* open the output fie for write only 
	 *	create it if it does not exist and Trincate the file 
	 * */
	outfd = open(outfname , (O_WRONLY |O_TRUNC | O_CREAT ), S_IRUSR | S_IWUSR);
	if(outfd == -1 ) {
		fprintf(stderr, "opening outfile failed");
		close(infd) ; 
		return -2;
	}

	/* Read from the output file and write to the input file*/ 

	while(!done){
		bytes_rd = read(infd , buf, BUFSZ) ;
		if(bytes_rd == -1){
			fprintf(stderr , "failed to read input file");
			ret = -4;
			break;
		}else if(bytes_rd == 0 ){break ;}
		count = (size_t)bytes_rd ; 
		while(count > 0 ){

		bytes_wr =	write(outfd, buf, count);
		if(bytes_wr == -1){
			fprintf(stderr , "failed to read input file");
			ret = -4;
		}else if(bytes_wr == 0 ) {break ; }
		count -= (size_t)bytes_wr ;
		bufadr = bufadr + bytes_wr;

		}

	}

	close(infd); 
	close(outfd);
	return ret;
}
