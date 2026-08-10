
#define  _DEFAULT_SOURCE
#include <sys/syscall.h>
#include <unistd.h>
#include <linux/io_uring.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stddef.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <linux/fs.h>
#include <string.h>
#include <errno.h>
#include <stdatomic.h>
#include <fcntl.h>

int io_uring_setup(unsigned entries , struct io_uring_params* p ){
	return (int)syscall(__NR_io_uring_setup ,entries , p );
}
int io_uring_enter(unsigned int fd , unsigned int to_submit , unsigned int min_complete , unsigned int flags ){
	return (int) syscall(__NR_io_uring_enter , fd , to_submit , min_complete , flags , NULL , 0 );
}

#define write_barrier() __asm__ volatile ("" ::: "memory");
#define read_barrier() __asm__ volatile ("" ::: "memory");

#define QUEUE_DEPTH 1 
#define BLOCK_SZ 1024 


int ring_fd ; 
unsigned *sring_tail , *sring_mask , *sring_array , *cring_tail , *cring_mask , *cring_head;
struct io_uring_sqe *sqes;
struct io_uring_cqe *cqes;
char buff[BLOCK_SZ];
off_t offset;
int app_setup(){
	struct io_uring_params p ={};
	void* sq_ptr , *cq_ptr;

	ring_fd = io_uring_setup(QUEUE_DEPTH , &p); 
	if(ring_fd <0  ){
		perror("erro setup");
		return 1;
	}
	size_t  sring_sz = p.sq_off.array + (p.sq_entries * sizeof(unsigned));
	size_t cring_sz = p.cq_off.cqes + (sizeof(struct io_uring_cqe) * p.cq_entries);
	
	if(!(p.features & IORING_FEAT_SINGLE_MMAP)){
		perror("requires 3 mmap");
		return 1;
	}
	if(sring_sz > cring_sz){
		cring_sz = sring_sz;
	}else{sring_sz = cring_sz ; }

	sq_ptr = mmap(0, sring_sz , PROT_READ | PROT_WRITE , MAP_ANONYMOUS | MAP_SHARED , ring_fd ,IORING_OFF_SQ_RING ); 
	if(sq_ptr == MAP_FAILED) {perror("mmap failed");return 1;}

	cq_ptr = sq_ptr ; 
	sring_tail = (unsigned int*)((char*)sq_ptr + p.sq_off.tail) ;
	sring_mask = (unsigned int*)((char*)sq_ptr + p.sq_off.ring_mask) ;
	sring_array = (unsigned int*)((char*)sq_ptr + p.sq_off.array) ;
	
	sqes = mmap(0 , p.sq_entries * sizeof(struct io_uring_sqe) , PROT_READ |PROT_WRITE , MAP_SHARED | MAP_POPULATE ,ring_fd , IORING_OFF_SQES);
	if(sqes == MAP_FAILED){
		perror(strerror(errno));
		return 1;
	
	}

	cring_head = (unsigned*)((char*)cq_ptr + p.cq_off.head);
	cring_tail = (unsigned*)((char*)cq_ptr + p.cq_off.tail);
	cring_mask = (unsigned*)((char*)cq_ptr + p.cq_off.ring_mask);
	cqes = (struct io_uring_cqe*)((char*)cq_ptr + p.cq_off.cqes);

	return 0;
}

int read_from_cq(){
	struct io_uring_cqe* cqe ; 

	unsigned int head ; 
	head =(unsigned int) atomic_load_explicit((_Atomic(unsigned int)*)cring_head , memory_order_acquire);
	while(head == atomic_load_explicit((_Atomic(unsigned int)*)cring_tail, memory_order_acquire)){
		usleep(1000);}
	read_barrier();
	cqe = &cqes[head & *cring_mask];
	if(cqe->res   <  0 ){
		fprintf(stderr , "Error ocuured int he file \n");

	}
	head++;
	atomic_store_explicit((_Atomic(unsigned int)*)cring_head , head , memory_order_release);
	return cqe->res ;
}

/* read and write zaa request to the submission queueu */ 

int submit_to_sq(int fd , int op ){
	unsigned index , tail ; 
	tail = *sring_tail;
	index = tail & *sring_mask ; 
	struct io_uring_sqe *sqe = &sqes[index]; 
	sqe->opcode = (unsigned char)op ; 
	sqe->fd = fd ; 
	sqe->addr = (unsigned long )buff ;
	sqe->off = (size_t)offset;
	if((unsigned char)op == IORING_OP_READ){
		memset(buff , 0x00 , BLOCK_SZ); 
		sqe->len = BLOCK_SZ ; 
	}else {
		sqe->len = (unsigned int)strlen(buff);
	}

	sring_array[index] = index ; 
	tail++ ;
	write_barrier();
	atomic_store_explicit((_Atomic(unsigned)*)sring_tail , tail , memory_order_release);


	int ret = io_uring_enter((unsigned)ring_fd , 1, 1,IORING_ENTER_GETEVENTS);
	if(ret < 0 ) { perror("iouring enter") ; return -1;}
	return  ret ; 
}
int main(){
	int res ; 

	if(app_setup()){
		fprintf(stderr , "Unable to setup uring\n");
		return 1;
	}
	
	while(1){
		submit_to_sq(STDIN_FILENO, IORING_OP_READ);
		res = read_from_cq();
		if(res > 0 ) {
			submit_to_sq(STDIN_FILENO,IORING_OP_WRITE);
			read_from_cq();
		}else if(res == 0 ){
			break ;
		}else {
			fprintf(stderr , "Error here %s\n" , strerror(abs(res)));
			break;
	}
		offset += res;
	}
	close(ring_fd);
	return 0;
}
