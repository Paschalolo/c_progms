#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(){
	printf("My process id is , pid = %u\n", getpid());
	printf("My parent process id , ppid = %u\n", getppid());
	printf("My group  id is , pid = %u\n", getgid());


}
