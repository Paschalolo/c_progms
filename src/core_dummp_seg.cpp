#include <cstdio>
#include <cstring>
#include <new>
int main(int argc , [[maybe_unused]] char** argv){
	void* bad_addr = reinterpret_cast<void*>(0xffffffffff601000);
	char *dest{nullptr} , src[] = "abscdefdddsss";
	auto ptr  = new (std::nothrow) char[256*1024];
	auto strln = strlen(src) ;
	if(!ptr){
		return -1;
	}
	
	if(argc == 1 ){
		dest  =  ptr;	
	}else {
		 dest = (char*)bad_addr;
	}

	std::memcpy(dest , src , strln);

	delete [] ptr;
	return 0;
}
