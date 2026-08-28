

#include <dlfcn.h>
#include <cstdio>

union func_t {
	void* ptr ; 
	int (*func) (int , int);
};
int main(int argc , char** argv ){
	func_t handle__{.ptr = nullptr}; 
	if(argc < 2 ){return -1;}
	auto dl_ptr  = dlopen(argv[1] , RTLD_LAZY);
	if( dl_ptr == nullptr) {
		return -2;
	}

	handle__.ptr =dlsym(dl_ptr ,"bod1" );
	if(handle__.ptr == nullptr) return -3;

	std::printf("%d\n", (*handle__.func)(89, 900)) ;
	dlclose(dl_ptr);
	return 0;
}
