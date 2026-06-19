#include <stdio.h>
#include <errno.h>


int main(int argc , char** argv){
	int ret ; 
	char* oldpath , *newpath ; 
	if(argc < 2){
		return -1;	
	}else{
		oldpath = argv[1] ; 
		newpath = argv[2];
	}

	ret = rename(oldpath, newpath); 
	if(ret == -1 ){
		fprintf(stderr , "Renamed failed\n");
		return -2;
	}
	return 0 ; 
}
