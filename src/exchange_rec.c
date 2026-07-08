/* 
 * Writing or reading protable data records 
 * machines with diffrent portable endian or reading it 
 * Authroied by Mr Ahanmisi Paschal 
 * Copyright 2024 - 2026 . All right reserved 
 */ 


#include <mysock.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define READF 1 
#define WRITEF 2 
#define Read "read" 
#define Write "write"
#define FNAME_LEN 32 
#define NRECORDS 2 
#define DEF_FILE_NAME "portable_recs"

#if defined(__BYTE_ORDER__) && (__ORDER_BIG_ENDIAN__ == __BYTE_ORDER__)
    #define IS_BIG_ENDIAN 1
#else
    // Fallback if compiler macros aren't available (assumes standard modern hardware)
    #define IS_BIG_ENDIAN 0 
#endif
/* Write the actual data records */


typedef struct data_reec_t{
	char m_name[32];
	uint32_t m_birthyear ; 
	uint32_t m_bonus ; 
	uint64_t m_salary ; 

}data_reec_t ;
[[maybe_unused]]constexpr bool  NEG = (sizeof(data_reec_t ) > 8);

int write_data(int fd ){
	data_reec_t datarec = {{0}, 1980 , 224000, 1234500,};

	size_t recsz ; 
	ssize_t bytes ; 
	recsz = sizeof(datarec);
	strcpy(datarec.m_name ,"jENIFER JOHNSON" );
	bytes = write(fd, (void*)&datarec , recsz);
	if(bytes == -1) {
		fprintf(stderr, "Error() : writedatarec () failed to write to data record ");
		close(fd);
		return -1;
	
	}
	if(bytes == (ssize_t)recsz){
		close(fd) ; 
		fprintf(stderr, "DId not write the full data");
		return -2;
	}

	return 0;
}

/* Write data recrods to a file */ 
int main(){

if (NEG){
	printf("neg");
}else {
	printf("no neg");
	} 
#if IS_BIG_ENDIAN
	printf("lets goo now biggy");
#else 
	printf("lets go");
#endif 
}
