#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys_hdrs.h>
void __attribute__((always_inline)) error_mssge(int errornum , const char* msg ){
	if(errornum > 0){
		fprintf(stderr , "%s\n" , strerror(errornum)); 
	}else{
		fprintf(stderr , "%s\n" , msg);
	}
}
void fatal_error(int erronum  , const char* msg){
	error_mssge(erronum ,msg); 
	exit(EXIT_SUCCESS);
} 
void usage_error(const char* msg){
	fprintf(stderr, "usage : %s\n", msg);
	exit(EXIT_SUCCESS);
}

