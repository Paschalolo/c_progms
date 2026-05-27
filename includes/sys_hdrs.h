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

 /* Flags ro pass to functions */ 
#define NO_TRAILING 1 
#define NON_NEG_ONLY 2
#define ONLY_DIGITS 4
#define POS_ONLY 8 
#define PURE (NO_TRAILING | ONLY_DIGITS)


/* Return codes */ 
#define VALID_NUMBER 1 
#define FATAL_ERROR -1 
#define TRAILING_CHARS_FOUND -2 
#define OUT_OF_RANGE -3 
#define NO_DIGITS_FOUND -4 
#define NEG_NUM_FOUND -5 

/** get_long()
 * On succesful processing it returns VALID_NUMBE and stores the resulting 
 * number in the *value , otherwise , it returns one of the non zerp error 
 * codes and purts a suitab;le message into *msg , flags is used to decide 
 * whether the trailing characters , negatve values and zeros for strings 
 * wu=ithout any digits are allowed or should be errors 
 *  
 *  @params char* arg [IN] string to parse 
 *  @params int flags [IN] Flag specifynig how to handle annomalies 
 *  @param long* value [OUT] Returned long int 
 *  @params char* msg[OUT] if not empty , error message 
 *  @return int VALID_NUMBER or a negative error code indicating type of error 
 * */
int get_long(char* arg , int flags , long* value , char* msg);
#endif
