#include <apie.h>
#include <sys/stat.h>

int main(){

	struct stat statbuf ; 

	if((stat("foo", &statbuf)) == -1){
		return -1;
	}
	if((chmod("foo" , statbuf.st_mode | S_IXGRP) == -1))return -1;
	return 0;
}
