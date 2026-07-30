

#include <sys/utsname.h>
#include <unp.h> 

int main(){
	struct utsname name ; 
	if(-1 == uname(&name ) ){
		return -1;
	} 
	constexpr unsigned int p_int {0x12345678};
	const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&p_int); 

	std::printf("OS VENDOR :%s %s\n", name.sysname, name.machine);
	if(ptr[0] == 0x78){
		std::printf("Little endian \n");
	}else if(ptr[0] == 0x12){
		std::printf("Big endian \n");
	}else{
		std::printf("Dont know dont want to know \n");;
	}
	return 0;
}
