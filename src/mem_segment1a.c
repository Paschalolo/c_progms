
#include <stdio.h>
#include <stdlib.h>

char globBuff[65536] ; 
int primes[] = {2, 3, 5, 7}; 



static int sqaure(int x){
	return x* x ;
}


static void docalc(int val ){
	printf("The sqaure of %d is %d\n" ,val , sqaure(val));
	int t ; /* Value is placed on the stack X86 mov [rsp+ 8] , t*/
	if(val < 1000) {
		t = val * val * val ; 
		printf("The cude is % d of % d" , t , val);
	}
}
int main(){
	static int key = 9973 ; /* Intiliazed in the data segment */ 
	[[maybe_unused]]static char mbuf[102400000] ; /* Vlaue is place in the .bss unitialized section */ 
	[[maybe_unused]]char*p ; /* Allocated int eh frame on the stack */ 
	p = malloc(1024); /* Value is allocated in the heap by incrementing the brk() function to move the .data section */ 

	docalc(key);
	return 0;
}
