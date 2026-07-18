/* File watching */ 
#include <sys/inotify.h>
#include <unistd.h>
#include <stdio.h>



constexpr size_t BUF_SIZE = sizeof(struct inotify_event) * 10;
int main(){
	int ifd , fd_f1 ; 
	__attribute__((aligned(4))) char data[BUF_SIZE];
	ssize_t len , i = 0 ; 

	return 0;
}
