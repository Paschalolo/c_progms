#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	printf(" pid :%d", getpid());
	printf(" ppid :%d", getppid());
	return 0;
}
