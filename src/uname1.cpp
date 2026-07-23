
#include <sys/utsname.h>

#include <cstdio>

int main(){
	struct utsname  buf ; 
	if(uname(&buf) == -1 )return -1 ; 
	std::printf("OS name : %s\nVersion : %s\nOS Machine : %s", buf.sysname , buf.release, buf.machine);
	return 0;	
}
