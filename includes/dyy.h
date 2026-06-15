
#ifndef SYS_PP
#define SYS_PP
struct Symbols ; 
extern struct Symbols ssy; 

int load_libary(const char* __restrict__ name ) ; 
void* pdy_symbol(const char* __restrict__ sym) ; 
int close_libary();
#endif
