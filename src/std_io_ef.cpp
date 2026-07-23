

#include <apie.h>
#include <cstdio>


int main(){
	int c ; 
	while((c= getc(stdin)) != EOF){
		if(putc(c, stdout) == EOF)err_sys("output error");
	}
	if(ferror(stdin)){
		err_sys("INput error");
	}
	return 0;
	}
