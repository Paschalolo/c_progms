

#include <cstddef>
#include <sys/mman.h>
#include <cstdio>
#include <unistd.h>
#include <err_tlp_v1.h>

#include <stdlib.h>
static void displayMincore(char* addr , size_t length ){
	unsigned char* vec; 
	long pageSize , numPages , j ; 
	pageSize = sysconf(_SC_PAGESIZE); 
	numPages = (static_cast<long>(length) + pageSize-1) / pageSize ; 
	vec = reinterpret_cast<unsigned char*>(malloc(static_cast<size_t>(numPages))) ; 
	if ( vec == nullptr ) {
		errMsg("Failed vec ()\n", ERRMSG_NOSET , -1);
	}

	if (mincore(addr ,length , vec ) == -1 ) {errMsg("mincore\n", ERRMSG_NOSET , -1);}

	for(j = 0 ; j < numPages ; j++){
		if(j % 64 == 0 ) 
	}
	free(vec);
}



int main(){
	
	return 0;
}
