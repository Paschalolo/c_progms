/* Program to get lic version 
 * By Paschal Ahanmisi
 * */ 

#include <gnu/libc-version.h>
#include <stdio.h>

int main(){
	printf("Version of GNU : %s" , gnu_get_libc_version());
	return 0;
}
