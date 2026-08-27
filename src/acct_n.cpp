

#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <err_tlp_v1.h>
int main(int argc , char** argv ){	
	if(argc < 3 ){
		std::fprintf(stderr , "%s <filename>\n", argv[0] ); 
		exit(1);	
	}
	
	if(acct(argv[1]) == -1 ) {
		errMsg("acct() failed \n", ERRMSG_NOSET , -1);	
	}
	std::printf("Process accounting %s \n" , argv[1]== nullptr ? "disabled" : "enabled");


	return 0 ; 
}
