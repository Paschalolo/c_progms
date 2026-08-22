

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
int main(int argc , char** argv ){	
	if(argc < 2 ) _exit(-1) ; 
	DIR* dire = opendir(argv[1]);
	if(dire == NULL) {
		fprintf(stderr , "Error or directory does not exitst");
		return -1;
	}
	struct dirent* dir_p ;
	errno = 0 ;  
	while((dir_p = readdir(dire)) != NULL){
		char* ptr = dir_p->d_name ; 
		if((strcmp(ptr , ".") == 0) || (strcmp(ptr, "..") == 0))continue ;
		printf("%s\n" , ptr);
	}
	
	if(errno != 0 ){printf("An error occured reading directory\n") ; return 0;}
	printf("Finished reading directory bye chow!!!\n");
	return 0 ; 
}
