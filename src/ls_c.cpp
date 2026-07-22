#include <cstdio>
#include <dirent.h>
#include <sys/types.h>

int main(int argc , char** argv ){
	DIR* dp ; 
	struct dirent* dirp ; 
	if (argc < 2 ) {
		std::fprintf(stderr , "Please enter a directroy ");
		return  -1 ; 
	}
	if((dp = opendir(argv[1])) == nullptr ) {
		std::fprintf(stderr , "could not open directory");	
		return -1;
	}
	
	while ((dirp = readdir(dp)) != nullptr ){
		std::printf("%s " , dirp->d_name);
		std::printf("%s\n" , (dirp->d_type == DT_REG ) ? "regular file": "Other stuff " );
	}
	closedir(dp);
	return 0;
}
