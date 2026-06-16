


/*
 *	Libary function source file 
 *	These functions demonstrate that one liabry can call another 
 *	libary function and a libary function can take input arguments and 
 *	return a value 
 *	Authored by Mr Paschal Ahanmisi 
 *	Copyright 2024-2026 Mr Paschal Ahanmisi
 * */

#include <string.h>
#include <stdio.h>

/*
 *	call another libary function to echo the input message 
 *	Return the length of the input message 
 * */

int echoMsg2(char*);
#if WINDOWS 
__declspec(dllexport) int __cdel echoMsg(char* msg)
#else 
int echoMsg(char* msg)
#endif
{
	printf("The libary function echoMsg() was called" );
	return echoMsg2(msg);	
}

int echoMsg2(char* msg ){
	printf("The libary function echoMsg2() was called");
	int len = 0 ;
	if(msg){
	len = (int)strlen(msg);
	printf("Your message is %s " , msg);
	}
	return len ; 
}
