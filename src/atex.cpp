#include <cstdlib>
#include <stdlib.h>
#include <cstdio>
void fun(){
	std::printf("Have fun bye");
}
int main(){
	atexit(fun);
}
