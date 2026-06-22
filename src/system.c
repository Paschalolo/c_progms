#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MYCMD "/bin/echo 'Hello there'"
int main(int argc , char** argv){
	int ret = 0 ; 
	char* cmd = MYCMD ; 
	
	if(argc > 1 ) {
		cmd = argv[1];
	}

	ret = system(cmd); 
	if(ret == -1 ) {
		fprintf(stderr , "Calling system() failed ");
		return -1 ; 
	}else {
		fprintf(stdout, "Running the command %s is returned %d", cmd , WEXITSTATUS(ret));
	}
	return 0;
}
