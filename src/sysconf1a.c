
#include <unistd.h> 
#include <errno.h>
#include <stdio.h>

static void  sysconfPrint(const char* msg , int name ){
	errno= 0 ;
	long lim ; 
	lim = sysconf(name); 
	if(lim == -1 ){
		printf("Inderterminable\n");
	}else {
		printf("%s : %ld" , msg , lim);
	}
}
int main(){
	
	sysconfPrint("_SC_ARG_MAX", _SC_ARG_MAX);
	sysconfPrint(" _SC_CHILD_MAX", _SC_CHILD_MAX );
	sysconfPrint("_SC_HOST_NAME_MAX",_SC_HOST_NAME_MAX );
	sysconfPrint("_SC_PAGESIZE",_SC_PAGESIZE );
	sysconfPrint(" _SC_LINE_MAX",  _SC_LINE_MAX);
	sysconfPrint("_SC_PHYS_PAGES",_SC_PHYS_PAGES );
	sysconfPrint("_SC_2_VERSION", _SC_2_VERSION);
	return 0;
}
