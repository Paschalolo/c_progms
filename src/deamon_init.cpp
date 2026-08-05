
#include <csignal>
#include <unp.h>
#include <syslog.h>

extern int daemon_proc ;
constexpr int MAXFD {64};

int deamon_init(const char* name, int facility ){
	int i ; 
	pid_t pid ; 
	if((pid = fork()) < 0){
		return -1; 
	}else if (pid){
		exit(0); 
	}

	if(setsid() < 0)return -1;

	signal(SIGHUP , SIG_IGN);
	if((pid = fork()) < 0){
		return -1; 
	}else if (pid){
		exit(0); 
	}
	daemon_proc = 1;
	chdir("/");

	for(i = 0 ; i < MAXFD ; i++){
		close(i) ;
	}

	open("/dev/null", O_RDONLY);
	open("/dev/null", O_RDWR);
	open("/dev/null", O_RDWR);

	openlog(name ,LOG_PID , facility);
	return 0;
}
int main(){
	
}
