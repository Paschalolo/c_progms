
#include <bits/types/struct_iovec.h>
#define  _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <linux/fs.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/io_uring.h>

constexpr int QUEUE_DEPTH = 1 ; 
constexpr int BLOCK_SZ = 1024 ; 

#define read_barrier() __asm__ volatile ("":::"memory");
#define write_barrier() __asm__ volatile ("":::"memory");

struct app_io_sq_ring /* submission queue */ {
	unsigned* head ; 
	unsigned* tail ; 
	unsigned* ring_mask ; 
	unsigned* ring_entries ; 
	unsigned* flags ; 
	unsigned* array ; 
};

struct app_io_cq_ring{
	unsigned* head ; 
	unsigned* tail ; 
	unsigned* ring_mask ; 
	unsigned* ring_entries ; 
	struct io_uring_cqe* cqes ; 
};

struct submitter {
	int ring_fd ; 
	struct app_io_sq_ring sq_ring ; 
	struct io_uring_sqe* sqes;
	struct app_io_cq_ring cq_ring ; 
};

struct file_info {
	off_t file_sz ; 
	struct iovec iovecs[];
};

int io_uring_setup(unsigned entries , struct io_uring_params*p){
	return (int) syscall(__NR_io_uring_setup , entries , p);
}
int io_uring_enter(int ring_fd , unsigned int to_submit , unsigned int min_complete , unsigned int flags){
	return (int) syscall(__NR_io_uring_enter , ring_fd , to_submit , min_complete , flags);
}

off_t get_file_size(int fd ){
	struct stat buf ; 
	if(fstat(fd , &buf) == -1){
		perror("fstat");
		return -1;
	}
	if(S_ISBLK(buf.st_mode)){
		return buf.st_blksize ;
	}else if (S_ISREG(buf.st_mode)){
		return buf.st_size ; 
	}
	return -1 ; 

}

int app_setup_uring(struct submitter* sub){
	struct app_io_cq_ring *cring = &sub->cq_ring; 
	struct app_io_sq_ring* sring  = &sub->sq_ring; 
	struct io_uring_params p ={};
	void* sq_ptr , *cqptr ; 
	sub->ring_fd = io_uring_setup(QUEUE_DEPTH , &p); 
	if(sub->ring_fd < 0 ){
		perror("Io uring setup");
		return 1;
	}
	int sring_sz = (int)( p.sq_off.array + (p.sq_entries * (unsigned)sizeof(unsigned)));
	int cring_sz = (int)( p.cq_off.cqes + (p.cq_entries * (unsigned)sizeof(struct io_uring_cqe)));
	if(p.features == IORING_FEAT_SINGLE_MMAP){
		if(cring_sz > sring_sz){
			sring_sz = cring_sz ; 
		}else{
			cring_sz = sring_sz;
		}

	}
	sq_ptr = mmap(0 , (size_t)sring_sz , PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS , sub->ring_fd , IORING_OFF_SQ_RING);
	if(sq_ptr == MAP_FAILED)return 1;
	if(p.features == IORING_FEAT_SINGLE_MMAP){
		cqptr = sq_ptr;	
	}else {
	cqptr = mmap(0 , (size_t)sring_sz , PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS , sub->ring_fd , IORING_OFF_CQ_RING);
	if(sq_ptr == MAP_FAILED)return 1;
	}
	sring ->head = (unsigned*)((char*)sq_ptr + p.sq_off.head); 
	sring->tail = (unsigned*)((char*)sq_ptr + p.sq_off.tail ); 
	sring->ring_mask = (unsigned*)((char*)sq_ptr + p.sq_off.ring_mask ); 
	sring->ring_entries = (unsigned*)((char*)sq_ptr + p.sq_off.ring_entries) ; 
	sring-> flags = (unsigned*)((char*)sq_ptr + p.sq_off.flags) ; 
	sring->array = (unsigned*)((char*)sq_ptr + p.sq_off.array) ;
	
	sub->sqes = mmap(0 , p.sq_entries * sizeof(struct io_uring_sqe) ,PROT_READ | PROT_WRITE , MAP_ANONYMOUS | MAP_SHARED , sub->ring_fd , IORING_OFF_SQES );

	if(sub->sqes == MAP_FAILED){
		return 1;
	}
	cring->head = (unsigned*)((char*)cqptr + p.cq_off.head);
	cring->tail = (unsigned*)((char*)cqptr + p.cq_off.tail);
	cring->ring_mask = (unsigned*)((char*)cqptr + p.cq_off.ring_mask);
	cring->ring_entries = (unsigned*)((char*)cqptr + p.cq_off.ring_entries);
	cring->cqes = (struct io_uring_cqe*)((char*)cqptr + p.cq_off.cqes);
	return 0 ; 
}

void ouput_to_console(char* buf , size_t len){
	while(len--){
	fputc(*buf++ ,stdout);	
	}
}

void read_from_cq(struct submitter* s){
	struct file_info* fi ; 
	struct app_io_cq_ring* cring = &s->cq_ring ; 
	struct io_uring_cqe* cqe ; 
	unsigned head , reaped = 0 ; 

	head = *cring->head ;

	do{
		read_barrier() ; 

		if(head == *cring->tail)break ;

		cqe = &cring->cqes[head & *s->cq_ring.ring_mask];
		fi = (struct file_info*) cqe->user_data ;
		if(cqe->res < 0 ){
			fprintf(stderr , "Error:%s\n" , strerror(abs(cqe->res));
		}
		int blocks = (int) fi->file_sz / BLOCK_SZ;
		if(fi->file_sz % BLOCK_SZ) blocks++ ; 


		for(int i = 0  ; i < blocks ; i++){
			ouput_to_console(fi->iovecs[i].iov_base , fi->iovecs[i].iov_len);
		}
	}while(1);
	*cring->head = head ;
	write_barrier(); 
}

int submit_to_sq(char* file_path , struct submitter* s ){
struct file_info* fi ;
	int file_fd = open(file_path , O_RDONLY);
	if(file_fd == -1 ) return 1;

	struct app_io_sq_ring* sring  = &s->sq_ring ;
	unsigned index = 0 , current_block = 0 , tail = 0 , next_tail= 0 ;
	off_t file_sz = get_file_size(file_fd); 

	if(file_sz < 0 ) return 1;
	off_t bytes_remaing = file_sz ; 
	int blocks = (int) file_sz / BLOCK_SZ ; 
	if(file_sz % BLOCK_SZ ) blocks++;
	fi = malloc(sizeof(*fi)+   sizeof(struct iovec)* (size_t)blocks);
	if(!fi) {
		return 1;
	}
	fi->file_sz = file_sz ; 

	while(bytes_remaing){
		off_t bytes_to_read = bytes_remaing ; 
		if(bytes_to_read > BLOCK_SZ) bytes_to_read = BLOCK_SZ ; 

		fi->iovecs[current_block].iov_len = (size_t)bytes_to_read ; 
		void* buf ; 
		if((buf = aligned_alloc(BLOCK_SZ, BLOCK_SZ)) == NULL) {
		return 1 ;}
		fi->iovecs[current_block].iov_base = buf; 
		current_block++;
		bytes_remaing -= bytes_to_read;
	}
}
int main(){

	return 0 ; 
}
