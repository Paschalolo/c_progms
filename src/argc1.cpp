
#include <cstdio>
int main(int argc , char** argv){
	for( auto i{0} ; i < argc ; i++){
		std::printf("%s", argv[i]);
	}
	return 0;	
}
