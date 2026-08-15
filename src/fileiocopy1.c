

#include "err_tlp_v1.h"
#include <tlp_v1.h>
#include <sys/stat.h>
#include <fcntl.h>

constexpr size_t BUF_SZ  = 1024 ;
int main(int argc , char ** argv){
	int input_fd , outputfd , openflags;

	mode_t permission ; 
	ssize_t nReads ; 
	char buf[BUF_SZ] ; 

	if (argc != 3 || (strcmp(argv[1] , "--help") == 0 ) ){
		errMsg("oldfile newfile \n",ERRMSG_NOSET,-1);
	}

	/* Open the input file */ 
	input_fd = open(argv[1] , O_RDONLY , S_IRWXU);
	if(input_fd == -1 ) {errMsg("opening file failed()\n",ERRMSG_NOSET , -1);}

	openflags = O_CREAT |  O_WRONLY | O_TRUNC; 
	permission = S_IRUSR  |  S_IWUSR | S_IRGRP| S_IWGRP ; 
	/* open or create output file */ 
	outputfd = open(argv[2] , openflags , permission);
	if(outputfd == -1 ){
		close(input_fd) ; 
		errMsg("Opening output file failed" , ERRMSG_NOSET , -1);
	}

	/* Transfer the data until we encounter a enf of file or error 
	*/
	while ((nReads = read(input_fd , buf , BUF_SZ)) >  0){
		if(write(outputfd ,buf , (size_t)nReads ) != nReads){
		errMsg("could not write the whole buffer" , ERRMSG_NOSET , -1);
		}
	}
	if(nReads == -1 )errMsg("Read\n",ERRMSG_NOSET, -1);

	close(input_fd); 
	close(outputfd);
	return 0 ;
}
