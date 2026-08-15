
#ifndef ERR_TLP_V1
#define ERR_TLP_V1
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
enum errmsg_t : int{
	ERRMSG_SET , 
	ERRMSG_NOSET
};
[[noreturn]] void errMsg(const char* __restrict__  msg , enum errmsg_t et , int ret );

/* Err msg to handle my error types */
__attribute__((noinline , cold)) void errMsg(const char* __restrict__  msg , enum errmsg_t et , int ret ){
	fprintf(stderr , "%s\n" , msg);
	if(et == ERRMSG_SET){
		fprintf(stderr , "Errno :%s\n" , strerror(errno));
	}	
	_exit(ret);
}
#endif 
