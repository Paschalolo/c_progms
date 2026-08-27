

#include <unistd.h>


char GREET[] { "GREET=salut" };
int main(){
	char * argvec[10] ;
	char* envec[] = { GREET ,  nullptr};
	return 0  ;
}
