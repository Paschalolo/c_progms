
#include <bits/types/sigset_t.h>
#define _GNU_SOURCE
#define _DEFAULT_SOURCE
#include <signal.h>
#include <string.h>
#include <stdio.h>
void printsigSet(FILE* fp , const char* prefix , const sigset_t *sigset){
	int sig , cnt ; 
	cnt = 0 ; 
	for(sig = 1 ; sig < NSIG ; sig++) {
		if(sigismember(sigset , sig)){
			cnt++;
			fprintf(fp , "%s%s%d" ,prefix ,strsignal(sig) , sig); 
		}
	}
	if(cnt == 0 )printf("empty signal set");
}
int main(){


	return 0;
}
