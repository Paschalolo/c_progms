

#include <unistd.h>
#include <stdio.h>


int main(){
	printf("Howdy today");
	[[maybe_unused ]]auto sz = write(STDOUT_FILENO , "HMM letgs go" , 12);
}
