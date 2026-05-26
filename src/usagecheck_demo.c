#include <stdio.h>
#include <stdlib.h>

int main(int argc , char** argv){
	if (argc < 3 ){
		fprintf(stderr , "Usage : %s file1 file 2 ", argv[0]); 
		exit(EXIT_SUCCESS);
	}
	printf("About to copy from %s to %s\n", argv[1] , argv[2]);
	// No code to fake copy yet 
 return 0;
}
