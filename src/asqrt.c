
#include <stdio.h>


float asqrt(float x){
	union ex{int ix ;float xi;}jj;
	jj.xi = x;
	jj.ix = 0x1fbb67a8 + (jj.ix >> 1);
	jj.xi = 0.5f * (jj.xi + (x/jj.xi));
	return jj.xi;
}

int main(){
	printf("%f" , asqrt(9.2f));
}
