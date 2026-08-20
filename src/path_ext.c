

#include <sys/statvfs.h>
#include <stdio.h>



int main(){
struct statvfs stv ; 
	if(statvfs("." , &stv) == - 1) return -1;

	printf("NUmber of inode %lu" , stv.f_files);
	printf("NUmber of  free inode %lu" , stv.f_ffree);
	printf("NUmber of inode %lu" , stv.f_fsid);
	return 0 ;
}
