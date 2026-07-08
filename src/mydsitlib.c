/* Some libary functions for disturbuted systems 
 * */ 
#include <stdio.h> 
#if defined(__BYTE__ORDER__) && (__ORDER_BIG_ENDIAN__)
	#define IS_BIG_ENDIAN 1
#else 
	#define IS_BIG_ENDIAN  0
#endif 

// defineing this equation for true portability 

enum ENDIAN_MODE : int{
	LITTLE_END =1, 
	BIG_END= 2,
};
int endian(){
	volatile unsigned int dword = 0x12345678; 
	unsigned char byte = *((unsigned char*)&dword) ;

	return (byte == 0x12) ? BIG_END : LITTLE_END; 
}

static int endian_mode = 0;
 __attribute__((constructor)) void setendianMode(){
	endian_mode = endian();
}

struct Mypad{
	unsigned int m_b ; 
	__attribute__((aligned(8))) char m_data[8];
};
int main(){
	printf("size of data is %lu", sizeof(struct Mypad));
}
