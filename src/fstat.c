
/*
 *
 *	Obtain information about a file 
 *
 * */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h> 
#include <fcntl.h>
#include <time.h> 
#include <langinfo.h>

#define MYFILE "./myfile"
#define DATE_BUFS 64

int cvt_time_to_date(time_t* time , char* date , unsigned int len){
	size_t nchars; 
	struct tm* tm ; 
	if((time == NULL) || (date == NULL) || (len <= 0 )){return -4;}
	tm = localtime(time);

	memset((void*)date , 0x00 , len);
	nchars = strftime(date, len , nl_langinfo(D_T_FMT), tm);

	if(nchars == 0 ) {
		return -5;
	}else{
		return 0;
	}
}


int main(int argc , char** argv){
	int ret ; 
	struct stat finfo; 
	char* fname ; 
	[[maybe_unused]] int fd ; 
	[[maybe_unused]]char date[DATE_BUFS];

	if(argc > 1 ) {fname = argv[1]; 
	}else{
		fname = MYFILE; 
	}
	// obtain informationnabout the file using stat
	//
	ret = stat(fname , &finfo); 
	if (ret != 0 ) {

		fprintf(stderr, "cannot get stats of the file");
		return -2;
	}

	printf("information about the file %s", fname);
	printf("device ID %lu", finfo.st_dev);
	printf("inode number %lu", finfo.st_ino);
	printf("info about the file type and mode %u", finfo.st_mode);
}
