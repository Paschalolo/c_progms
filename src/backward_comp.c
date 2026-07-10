/* Backward compatibility explained*/

#include <stdio.h>
struct func_t{
	int m_data ; 
	char m_padd[16 - sizeof(int)];
};

enum DATA: int {
	ALLY , 
	SALLY
};
struct func1_t {
	int m_data ;
	int m_byte ;
	alignas(8) char m_pod[8]; 
	double m_joy;
};
struct func2_t {
	int m_data ;
	int m_byte ;
	int m_joy;
	alignas(8) char m_pod[8]; 
	double m_joy1;
};

void connect_joy_func1(struct func1_t* fn){
	printf("FOund out func1_t byte %d  , %f", fn->m_byte , fn->m_joy);
}
void connect_joy_func2(struct func2_t* fn){
	
	printf("FOund out func1_t byte %d  , %f", fn->m_byte , fn->m_joy1);
}
void connect_tojoy(struct func_t* fn){
	switch(fn->m_data){
		case SALLY :
			connect_joy_func1((struct func1_t *)fn);
		case ALLY:
			connect_joy_func2((struct func2_t*)fn);
	}
	return ;
}
