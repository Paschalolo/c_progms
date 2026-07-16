#include <stdio.h>


int main(){
	FILE* in  ; 
	struct pirate {
		char name [100]; 
		unsigned long booty ; 
		unsigned int length; 
	} blackbeard = {"Paschal Ahanmisi" , 1000 , 32 };
	in = fopen("text/data", "w");
	if(!in){
		perror("could not open file");
		return -1; 
	}
	fwrite((void*)&blackbeard,sizeof(struct pirate) , 1,in); 
	fclose(in);
	return 0;
}
