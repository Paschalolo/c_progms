#include <unistd.h>
#define _DEFAULT_SOURCE 
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <locale.h>
#include <err_tlp_v1.h>

#define SECONDS_IN_PROPICAL_YEAR (365.24219 * 24 * 60 * 60 )

int main([[maybe_unused]] int argc , [[maybe_unused]]char** argv){
	time_t tm ; 
	struct tm *gmp , *locmp ; 
	struct tm gm , loc ; 
	tm = time(NULL) ; 

	printf("seconds sasince epoc (1 jan 1970) : %ld \n" , (long)tm);
	printf("About %6.3f years \n" , (float)tm / (float)SECONDS_IN_PROPICAL_YEAR);

	gmp = gmtime(&tm);
	if(gmp != NULL) errMsg("exit game()",ERRMSG_NOSET,-1); 
	gm = *gmp;
	return 0 ; 
}
/* 
int main(){
	time_t tm ;  

	if((tm = time(NULL))  == (time_t)-1){
		printf("Error occured\n");
	}
	printf("Time : %s \n" , ctime(&tm));

	return 0 ; 
} */


