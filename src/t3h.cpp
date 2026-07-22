
#include <apie.h>

constexpr  char FILENAMES[8][25]{
	"Block file", "Character file" , 
	"Directory" , "FIFO file", 
	"Regular file" , "Symbolic file" , 
	"Socket file" , "Error "
};
int main(int argc , char** argv ){
	int ret  ; 
	struct stat buf ; 
	const char*ptr ; 
	if(argc < 2 )return -1;
	for(auto i{1uz} ; i < static_cast<size_t>(argc) ; i++ ){
		printf("%s : ", argv[i]);
		if((ret = stat(argv[i] , &buf)) == -1 ) {
			err_sys("lstat error "); 
		}
		if( S_ISBLK(buf.st_mode)){
			ptr = &(FILENAMES[0][0]); 
		}else if ( S_ISCHR(buf.st_mode)){
			ptr = &(FILENAMES[1][0]); 
		}else if(S_ISDIR(buf.st_mode)){
			ptr = &(FILENAMES[2][0]); 
		}else if(S_ISFIFO(buf.st_mode)){
			ptr = &(FILENAMES[3][0]); 
		}else if (S_ISREG(buf.st_mode)){
			ptr = &(FILENAMES[4][0]); 
		}else {
			ptr = &(FILENAMES[7][0]);
		}

	}
	printf("%s\n", ptr);
	return 0;
}
