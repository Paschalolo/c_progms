#define  _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
bool is_page_boundary(void* ptr){
	return !((uint64_t)ptr & (4096UL-1UL));
}

int main(){
	printf("%p", sbrk(0));
	printf("%s", is_page_boundary(sbrk(0)) ? "is page aligned " : "not page aligned");


}
