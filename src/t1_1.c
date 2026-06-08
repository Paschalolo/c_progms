#include <stdio.h>

extern int test_func(int);


int main(){
	printf("%d", test_func(90));
	return 0; 
}
