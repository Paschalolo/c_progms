
#include <unistd.h>


int set_highest_prioriy(pid_t pid){
	struct sched_param schd ={0}; 
	int policy , max , ret ; 
	policy = sched_getscheduler(pid) ; 
	if (policy == -1 ) {
		return -1;
	}

	max = sched_get_priority_max(policy) ; 
	if(max == -1 ) return -1; 
	schd.sched_priority = max ; 
	ret = sched_setparam(pid , &schd); 
	return ret ;
}
