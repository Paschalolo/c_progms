#include <stdio.h>
#define __STDC_LIB_EXT1__
int main(){
	char name[256] = {0};

	printf("Enter name : ");
	[[maybe_unused]]int a = scanf("%s", name);
	printf("%s", name);
	return 0;
}
