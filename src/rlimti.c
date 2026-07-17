/* Total amount of memoery the process can lock in memeory
 * This can be called with mlock() or mmap -> MMAP_LOCKED 
 * to lock the memory into place */
#include <sys/resource.h>
#include <sys/time.h>
#include <stdio.h>



int main(){
	struct rlimit rlt ; 
	int ret ;
	ret =getrlimit(RLIMIT_MEMLOCK, &rlt );
	if(ret == -1){return -1;}
	printf("Locked memroy limit : %ld\n", rlt.rlim_max);
	ret =getrlimit(RLIMIT_CORE , &rlt );
	printf(" cur : %ld , Max RLIMIT_CORE : %ld\n", rlt.rlim_cur , rlt.rlim_max);
	return 0;
}
