#include <stddef.h>
#define  _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>


int main(){
	void* addr = sbrk(0); 
	if(addr == (void*)-1) _exit(-1);

	printf("old addr : %p\n" , addr) ; 
	// check alignmet on 8 bytes boundary 
	 void* new_ptr = !((size_t)addr & 7ULL) ? (void*)((size_t)addr+ 1000) : (void*)(((((size_t) addr ) + 8)  & ~(7ULL)) + 1000 );
	 printf("value : %ld " , ((intptr_t)new_ptr - (intptr_t)addr));
	addr = sbrk((intptr_t)new_ptr - (intptr_t)addr);
	printf("new :ddr = %p\n" , sbrk(0));
		
}
