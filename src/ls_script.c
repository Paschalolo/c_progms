

#define _GNU_SOURCE
#include <sys/syscall.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
 struct linux_dirent64 {
               ino64_t        d_ino;    /* 64-bit inode number */
               loff_t         d_off;    /* Not an offset; see getdents() */
               unsigned short d_reclen; /* Size of this dirent */
               unsigned char  d_type;   /* File type */
               char           d_name[]; /* Filename (null-terminated) */
           };

[[maybe_unused]]constexpr size_t BUF_SIZ = 1024 ;
constexpr size_t ld_size = sizeof(struct linux_dirent64);
int main([[maybe_unused]] int argc ,[[maybe_unused]] char** argv){
	
	int fd ; 
	char* file_name ; 
	ssize_t ret ; 
	__attribute__((aligned(32))) char buf[BUF_SIZ] ;
	if(argc > 1 ) {
		file_name = argv[1];
	}else {
		file_name = ".";
	}
	fd = open(file_name ,O_RDONLY |  O_DIRECTORY ,S_IRWXU  );

	if(fd == -1 ) {
		if(errno == ENOTDIR) {
			printf("%s\n" , file_name );
		}else {
			fprintf(stderr , "An error or issue occured\n");
			printf("%s" , strerror(errno));
		}
		exit(1);
	}

	ret = getdents64(fd,buf,BUF_SIZ);
	if(ret == -1 ) {
		fprintf(stderr ,"not directory\n");
		exit(1);
	}else if (ret == 0 ) {
		return 0;
	}
	for(ssize_t i = 0 ; i < ret ; i+= (ssize_t)ld_size ){
		unsigned char type = ((struct linux_dirent64*)(buf + i))->d_type ;
		if( type == DT_DIR  || type == DT_REG ) {
		printf("%s " , ((struct linux_dirent64*)(buf + i))->d_name );
		}
	}

	return 0;
}
