#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <sys_hdrs.h>

int get_long(char *arg, int flags, long *value, char *msg){
	char* endptr = NULL ; 
	long val ; 
	errno = 0 ; 
	val = strtol(arg, &endptr , 0);
	if(errno == ERANGE){
		if(msg != NULL ){sprintf(msg,"%s\n", strerror(errno));}
		return FATAL_ERROR; 
	}
	if(endptr == arg){
		if(flags & (ONLY_DIGITS | NO_TRAILING)){
			if(msg != NULL){

		sprintf(msg,"No digits in the string ");
		return NO_DIGITS_FOUND;
			}else{
				*value = 0 ; 
				return VALID_NUMBER;
			}
		}
	}
	if(*endptr != '\0'){
		if(flags & NO_TRAILING){

			return TRAILING_CHARS_FOUND; 
		}
	}
	return VALID_NUMBER; 
}
