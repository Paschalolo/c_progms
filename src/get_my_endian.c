#include <stdio.h>

enum Endians: int{
	BIG_ENDIAN , 
	LITTLE_EDIAN ,
};
int endian(){
	volatile unsigned int dword = 0x12345678 ; 
	unsigned char* byte =(unsigned char*)&dword ; 
	return (byte[0] == 0x12 ) ? BIG_ENDIAN : ((byte[0] == 0x78) ? LITTLE_EDIAN : -1);
}

int main(){}
