

#include "err_tlp_v1.h"
#include <sys/utsname.h>
#include <stdio.h>


int main(){
	struct utsname uu ;
	if(uname(&uu) == -1){errMsg("Uname() failed " , ERRMSG_NOSET , -1);}
	printf("Operating system name : %s\n" , uu.sysname);
	printf("Node name  : %s\n" , uu.nodename);
	printf("Operating system release : %s\n" , uu.release);
	printf("Versiion  %s\n" , uu.version);
	printf("Hardware tyepe : %s\n" , uu.machine);
#ifdef _GNU_SOURCE
	printf("domain naem  : %s\n" , uu.domainname);
#endif 
	return 0;
}
