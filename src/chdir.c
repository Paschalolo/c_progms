#include <unistd.h>
#include <stdio.h> 
#include <string.h>
#include <errno.h>

#define NEW_WORK_DIR "."
int main(){
	int ret ; 
	long len ; 
	cahr* buf = NULL ; 
	char* path ; 

	len = pathconf("." , __PC_PATH_MAX);;

	return 0 ; 
}
