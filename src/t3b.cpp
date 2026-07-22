
#include <apie.h>
#include <unistd.h>
int main(){
	printf("Hello world from process ID : %d\n", getpid());
	exit(0);
}
