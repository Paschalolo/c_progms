
#include <apie.h>
#include <pwd.h>
#include <sys/types.h>
#include <cstring>

int main(){
	struct passwd *ptr ;
	char name[] = "Loyal";
	setpwent(); 
	while((ptr = getpwent()) != nullptr){
		if(std::strcmp(name , ptr->pw_name) == 0 )break; 
	}
	endpwent(); 
	return 0;
}
