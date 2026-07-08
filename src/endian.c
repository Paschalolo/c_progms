#include <stdint.h>
#include <stdio.h>


int main(){
	uint64_t hex = 0x12345678;
	uint8_t byte   = *(((uint8_t*)&hex) + 3 );
	printf("%2X" , byte );
	return 0;
}
