#include <apie.h>

#include <cstdio>
#include <unistd.h>


int main(int argc , char** argv){

	if(argc < 2 ) return -1 ; 
	if((access(argv[1], R_OK)) < 0) err_sys("File does not exits or cannot be accessed by our process\n ");
	std::printf("read access okay");
	return 0;
}
