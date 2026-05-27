#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>

#ifndef COMMON_HD
#define COMMON_HD
#define STRING_MAX 1024 


/*Definitions used by locale*/
#define FORMAT "%c" 
#define BAD_FORMAT_ERROR -1
#define TIME_ADJUST_ERROR -2
#define LOCALE_ERROR -3 

/* General errors*/ 
#define READ_ERROR -4 
#define MEM_ERROR -5 


#endif
