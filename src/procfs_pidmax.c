
#include <fcntl.h>
#include <err_tlp_v1.h>
#include <sys/stat.h>
#include <unistd.h>

constexpr size_t MAX_LINE = 1024 ; 
int main(int argc , [[maybe_unused]] char** argv ){
	int fd ; 
	char line [MAX_LINE];

	fd = open("/proc/sys/kernel/pid_max" , (argc > 1 ) ? O_RDWR : O_RDONLY , S_IRWXU);
	if(fd == -1 ){errMsg("open() failed" ,ERRMSG_NOSET,-1) ; }

	ssize_t n = read(fd ,line ,  MAX_LINE);
	if(n == -1 ) _exit(-1) ;
	line[n] = 0x00 ;
	printf("%s" , line);
	return 0;
}
