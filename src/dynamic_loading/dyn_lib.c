#include <dyy.h> 
#include <stdlib.h>
#include <stdio.h>
int main([[maybe_unused]] int argc , [[maybe_unused]] char** argv){
	if(argc < 2){
		fprintf(stderr, "error no file");
		exit(1);
	}
	printf("%s %s", argv[1] , argv[2]);
	int res ; 
	res = load_libary(argv[1]);
	if(res != 0){
		fprintf(stderr, "couldnt load libary");
		exit(1);
	}
	typedef union func_t {
		void* ptr ; 
		int (*func1)(int); 
	}func_t;
	func_t yh ={ NULL}; 

	yh.ptr = pdy_symbol(argv[2]); 
	int va =  yh.func1(88);
	printf("%d", va);
	close_libary();
	
	printf("finito");
}

