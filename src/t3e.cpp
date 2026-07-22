
#include <apie.h>
#include <errno.h>
#include <climits>
#include <linux/limits.h>
#include <unistd.h>
#ifdef PATH_MAX 
static long pathmax = PATH_MAX ; 
#else 
static long pathmax = 0 ; 
#endif 

static long posix_version{0}; 
static long xsi_version{0};


constexpr long  PATH_MAX_GUESS {1024};

char* path_alloc(size_t* sizep){
	char* ptr ; 
	size_t size ; 

	if (posix_version == 0 ) {xsi_version = sysconf(_SC_VERSION);}

	if(xsi_version == 0 ) xsi_version = sysconf(_SC_VERSION);
	if(pathmax = pathconf("/" , PATH_MAX_GUESS))
}
int main(){
	
	return 0;
}
