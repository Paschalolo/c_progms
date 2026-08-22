
#define   _DEFAULT_SOURCE 
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/sysmacros.h>

static void displayStat(const struct stat* st){
	printf("File type:                    ");
	switch((st->st_mode & S_IFMT)){
		case S_IFBLK :
			printf("Block device \n");
			break ; 

		case  S_IFCHR : 
			printf("char device \n");
			break ; 

                case S_IFIFO :     
			printf("FIFO device \n");
			break ; 
		case S_IFREG : 
			printf("Regular  device \n");
			break ; 
                case S_IFDIR:    
			printf("Directory device \n");
		break;
		case S_IFLNK :    
			printf("Symbolic link\n");
			break ; 
                case S_IFSOCK: 
			printf("Socket \n");
			break ;
	}

	printf("Device containing i-node : major:%d minor = %d \n" ,major(st->st_dev) , minor(st->st_dev));
	printf("I node numbre :                     %ld\n" , st->st_ino);
	printf("Mode :  	%lu\n" , (unsigned long) st->st_mode );
	printf("Optimal IO size : %ld\n" , st->st_blksize) ;
}
