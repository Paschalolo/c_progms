#include <cstdio>
#include <sys/resource.h>
#include <climits>
int main(){
	struct rlimit rlm ;
	if(getrlimit(RLIMIT_STACK, &rlm) == -1) return -1;
	std::printf("sack cur %lu , stack max limit %s ", rlm.rlim_cur , (rlm.rlim_max == ULLONG_MAX ) ? "Ulmited" : "not unlimited");
	return 0;
}
