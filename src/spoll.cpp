
#include <sys/select.h>
#include <unp.h>
#include <algorithm>
void str_cli(FILE* file , int sockfd ){
	int maxfd1 , stdlineof ; 
	fd_set rset ; 
	char buf[MAX_LINE] ; 
	int n ; 

	stdlineof = 0 ; 
	FD_ZERO(&rset); 
	for(;;){
		if(stdlineof == 0 ) {
			FD_SET(fileno(file) , &rset); 

		}
		FD_SET(sockfd , &rset); 
		maxfd1 = static_cast<int>(std::max(fileno(file) , sockfd) + 1) ;
		if(select(maxfd1 , &rset , nullptr , nullptr , nullptr) == -1) {
			err_sys("selcet() failed");
		}
		ssize_t rr = write()
	}
	
}


int main(){


	return 0;
}
