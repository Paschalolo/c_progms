
#include <csignal>
#include <signal.h>
#include <apie.h>
#include <cstdio>
static void sig_init(int);
constexpr int MAXLINE = 256 ;
int main(){
	char buf[MAXLINE]; 
	pid_t pid ; 
	int status ; 


	if(signal(SIGINT , &sig_init) == SIG_ERR){
		err_sys("signal  failure ");
	}
	printf("%%"); 
	while(){

	}
	
}
