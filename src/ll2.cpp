

#include <unistd.h> 
#include <cstdio> 

int main(){
	int ret ; 
	ret = truncate("./pirate.txt" , 45);
	if(ret == -1) {
		std::fprintf(stderr , "Error here \n");
		return 1;
	} 
	return 0;
}
