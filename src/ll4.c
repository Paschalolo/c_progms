

#include <unistd.h>
#include <stdio.h>

int main(int argc , [[maybe_unused]] char** argv){
	char** ptr = nullptr ;
	if(argc < 2) {printf("Only oner argument \n");}else {
		ptr = &(argv[2]);
	}
	printf("function excution started\n");
	execv(argv[1] ,ptr);
	printf("function excution finished\n");
	return 0;
}
