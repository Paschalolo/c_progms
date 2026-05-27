#include <cstddef>
#include <cstdlib>
#include <ctime>
#define _GNU_SOURCE
#include <error_exit.h>
#include <sys_hdrs.h>

int main(int argc , char** argv){

	char formatted_date[200] = {0} ; 
	time_t current_time ; 
	struct tm* broken_down_time ; 
	char format_str[1024];
	strcpy(format_str , "%c");
	current_time = time(NULL);

	/* convert curren tim into broken down time */ 
	if((broken_down_time = localtime(&current_time))== NULL){
		fatal_error(EOVERFLOW, "localtime");
	}
	if(strftime(formatted_date , sizeof(formatted_date), format_str, broken_down_time) == 0 ){
		fatal_error(EXIT_FAILURE, "convertin gto date time string failed to prodcue an empty string"); 
	}
	printf("%s\n", formatted_date);
	return 0;
}
