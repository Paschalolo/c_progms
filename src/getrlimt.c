
/*
 *	Get resources of a process 
 *	\Copyright (c) 2024 - 2026
 * */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/resource.h>

#define RSCNAME_LEN 24 
#define NUM_RSCNUAME 16 

struct rscname {
	unsigned int idx;
	alignas(8) char rsname[RSCNAME_LEN +1 ];
};

struct rscname names[NUM_RSCNUAME] = {
	{ 0 , "RLIMIT_CPU"}, 
	{1, "RLIMIT_FSIZE"},
	{2 , "RLIMIT_DATA"}, 
	{3 , "RLIMT_STACK"},
};
