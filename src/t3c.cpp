#include <apie.h>
#include <cerrno>
#include <cstring>
#include <errno.h>


int main(){
	fprintf(stderr , "EACCESS : %d %s" ,EACCES,  strerror(EACCES));
	return 0;
}
