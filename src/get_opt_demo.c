#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc , char** argv){

	int ch; 
	char options[] = ":hb::c:1"; 
	bool opt_h = false, opt_1 = false , opt_b = false , opt_c = false ; 
	char b_arg[32] = {0x00}; 
	char c_arg[32] = {0x00};

	opterr = 0;
	while(true){
		ch = getopt(argc, argv , options);
		if(ch == -1)break ; 
		switch(ch){
			case 'h': 
				opt_h = true; 
				break ; 
			case 'b' : 
				opt_b = true; 
				break ; 
			case 'c' : 
				opt_c = true; 
				break ; 
			case '1' : 
				opt_1 = true ; 
				break ; 
			case '?' : 
				printf("Found invalid options %c\n", optopt);
				break ; 
			case ':' :
					printf("Missing required arguments\n"); 
					break ; 
			default : 
				printf("?? getopt returend character code 0%o ??", ch); 

		}
	}
	printf("Options found :\n"); 
	if(opt_h) printf("-h"); 
	if(opt_1) printf("-1");
	if(opt_b){
		printf("b");
		if(strlen(b_arg) > 0 ){
			printf("with arguments %s \n", b_arg);
		}else{
			printf("With no arguments \n");
		}
	}
	if(opt_c) {
		printf("-c with arguments %s\n", c_arg); 
	
		if(optind < argc){
		printf("non-option ARGV elements: \n");
		while(optind < argc){
			printf("%s" , argv[optind++]);
			printf("\n");
		}
		}
	}
	return 0;
}
