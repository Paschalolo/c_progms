/* HEADER FILE BY PASCHAL AHANMISI */ 

#ifndef HH_PP_Y
#define HH_PP_Y 
#include <stdio.h>
#include <stdlib.h>
void err_sys(const char* __restrict__ str){
	fprintf(stderr , "%s" , str);
	 exit(1);
}
#endif 
