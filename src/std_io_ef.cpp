

#include <apie.h>
#include <cstdio>

extern void vul();
int main(){
	int c ; 
	while((c= getc(stdin)) != EOF){
		if(putc(c, stdout) == EOF)err_sys("output error");
	}
	if(ferror(stdin)){
		err_sys("INput error");
	}
	vul();
	return 0;
	}
