#define  _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
	char name[256] = {0};
	int a =gethostname(name , 256);
	if(a == -1 )exit(1);
	printf("%s", name);
	return 0;
}
