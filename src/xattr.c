

#include <sys/xattr.h>
#include <stdio.h>
#include <stdlib.h>

#define XATTR_SIZE 10000

static void usageError(char* progName ){
	fprintf(stderr , "Usage %s file .... \n" , progName) ;
	exit(-1) ;
}


int main(){
	char list[XATTR_SIZE] , value [XATTR_SIZE] ;
	ssize_t listlen , valueLen ; 
	int ns , j , k , opt ; 
	bool hexdisplay  ; 
	while ()
	return 0 ; 
}
