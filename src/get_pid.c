#include <unistd.h>
#include <stdio.h>


int main(){
	printf("The i am of the process %d", getpid());
	return 0;
}
