#include <stdlib.h>
#include <stdio.h> 


int main(){
	char* name = getenv("SHELL");
	printf("The current shell is %s ", name);
	
}
