#define  _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
int main(){
	char name[2] = {0};
	int a =gethostname(name , 2);
	if(a == -1 ){
		switch(errno){
			case EFAULT : 
				printf("Name is invalid");
				break;	
			case ENAMETOOLONG:
				printf("Name is truncated and too long lost some value");
				break; 
			case EINVAL : 
				printf("size is negative than the actual size");
				break;
		}
		exit(1);
	}
	printf("%s", name);
	return 0;
}
