

#include <cstdio>
#include <stdlib.h>

using u64 = unsigned long ; 

static inline __attribute__((always_inline)) u64 get_rcx(void){
	u64 reg_val ;
	__asm__ volatile(
			".intel_syntax noprefix \n\t"
			"push rdx\n\t"
			"pop %0\n\t"
			".att_syntax\n\t"
			: "=r"(reg_val)/* output regiisters */ 
			:/* input registers */
			: /* clober flags */
			);
	return reg_val;
}
int main(){
	long long b = 9000;
	auto v = get_rcx();
	printf("NUmber  : %lld", b);
	printf("values of rsi : %ld", v);
	return 0;
}
