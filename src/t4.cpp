 #include <sys/sysmacros.h>
#include <apie.h>


int main(int argc , char** argv){
	struct stat buf ; 
	if(argc < 2 ) return -1 ; 
	if((stat(argv[1] , &buf)))return 1;
	printf("dev : %d/%d" , major(buf.st_dev), minor(buf.st_dev));


	return 0;
}
