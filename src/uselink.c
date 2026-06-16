
/*
 *	This program demonstrates calling functions in libaries of our own 
 *	via static or dynamic linking 
 *	Authored by Mr Paschal Ahanmisi
 *	Copyright 2020-2026 Mr Paschal Ahanmisi
 * */

#include <stdio.h>

extern int tripleIt(int);
extern int echoMsg(char*);
int main(){
	int ret; 
	int x = 22 ; 
	char* mymsg = "Hello there!" ;

	/* Pass in an integr and get back another */ 
	ret = echoMsg(mymsg);
	printf("echomsg = %d  , %d", x ,ret);
	ret = tripleIt(x);
	printf("echomsg = %d  , %d", x ,ret);
	return 0;
}
