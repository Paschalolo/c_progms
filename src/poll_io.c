#include <poll.h>
#include <sys/poll.h>
#include <unistd.h>
#include <stdio.h>


int main(){
	struct pollfd m_pd[2];
	int ret ; 
	ssize_t rr;
	/* watch for ability to read */ 
	m_pd[0].fd = STDIN_FILENO ; 
	m_pd[1].events = POLLIN ;
	/* Watch for abiiility to write */ 
	m_pd[1].fd = STDOUT_FILENO ; 
	m_pd[1].events = POLLOUT ; 

	/* All set block */ 

	ret = poll(m_pd , 2 , (5*1000)); 
	if(ret == -1) {
		perror("poll");
		return -1;
	}
	if(m_pd[0].revents == POLLIN )printf("stdin is readable"); 

	if(m_pd[1].revents == POLLOUT )printf("stdout is writeable");
	
#define SZ 125 
	char buf[SZ] ; 
	rr =read(STDIN_FILENO, buf , SZ);
	if(rr == -1) {
		return -2;
	}
	buf[rr] = 0x00 ; 
	rr = write(STDOUT_FILENO , buf , SZ);
	if(rr == -1)return -3;
	return 0;

	return 0;
}
