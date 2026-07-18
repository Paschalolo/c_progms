#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(){
	char name[256] ; 

	char* ptr ; 
	errno =0 ;
	ptr = getcwd(name , 256);
	if(!ptr){
		if(errno == ERANGE) {
			fprintf(stderr ,"Overflwo set to NULL");
			return -2;
		}
		return -1 ; 
	}

	printf("%s \n", name);

	return 0;
}
