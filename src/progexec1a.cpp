

#include <unistd.h>
#include <stdlib.h>

[[maybe_unused]] char GREET[] { "GREET=salut" };
int main(){
if(	system("ls | wc") == -1) exit(-1);
	return 0  ;
}
