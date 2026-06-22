/* 
 * Create a child process to run a new program with execl() function  
 * Copyright (c) 2024 -  2026
 */ 

#define PROG_NAME "myprog" 
#define PROG_PPATH "./myprog" 
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	pid_t pid ;
	int ret ; 

	pid = fork(); 

	if(pid == -1) {	
		fprintf(stderr , "fork failed()") ;
		return 1; 
	}else if (pid == 0  ){
		char arg1[8] = "8";
		printf("I am new born child \n");
		ret = execle(PROG_NAME, PROG_PPATH, (char*) arg1);
		printf("chil;d execlve () returned" );
		return 0 ; 
	}
	return 0 ; 
}
