
#include <apie.h>
#include <unistd.h>
constexpr int BUFFSIZE {4096};


int main(){
	ssize_t n ; 
	char buf[BUFFSIZE] ; 

	while((n= read(STDIN_FILENO, buf, BUFFSIZE)) > 0){
		buf[n] = 0x00 ;
		if(write(STDOUT_FILENO , buf , static_cast<size_t>(n)) != n){
			err_sys("write error");
		}
		if(n < 0 ) {
			err_sys("read error");
		}
	}
	return 0;
}
