

#include <linux/limits.h>
#include <sys/inotify.h>
#include <stdio.h>
#include <sys/types.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static void displayInotifyInformation(struct inotify_event* i){
	printf("wd : %d\n", i->wd);
	if(i->cookie > 0 ) printf("cookie : %d", i->cookie);

	printf("mask = ");
	if(i->mask & IN_ACCESS )printf("Fiel was accessed\n");
	if(i->mask & IN_ATTRIB  )printf("Fiel was accessed IN_ATTRIB  \n");
	if(i->mask & IN_CLOSE_WRITE )printf("Fiel was accessed IN_CLOSE_WRITE\n");
	if(i->mask & IN_CREATE )printf("Fiel was accessed\n");
	if(i->mask & IN_DELETE )printf("Fiel was accessed IN_DELETE\n");
	if(i->mask & IN_MODIFY  )printf("Fiel was accessed IN_MODIFY \n");
	if(i->mask & IN_MOVE_SELF)printf("Fiel was accessed IN_MOVE_SELF \n");
	if(i->mask &   IN_OPEN  )printf("Fiel was accessed   IN_OPEN \n");
}

constexpr size_t BUF_LEN = sizeof(struct inotify_event) + NAME_MAX + 1 ; 
int main(int argc , char** argv ){
	int inotifyfd , wd , j  ; 
	char buf [BUF_LEN];
	ssize_t num_read ; 
	char* p ; 
	struct inotify_event* event ; 

	if(argc < 2 ) exit(1);
	inotifyfd = inotify_init();
	if(inotifyfd == -1 ) exit(-1) ; 

	for(j = 1 ; j < argc ; j++){
		wd =inotify_add_watch(inotifyfd , argv[j] , IN_ALL_EVENTS);
		if(wd == -1) exit(-1);
	}

	for(;;) {
		num_read = read(inotifyfd , buf , BUF_LEN);
		if(num_read <= 0 ) exit(-1) ;
		printf("Read %ld bytes from inotify fd %d \n" , num_read , inotifyfd);
		for(p = buf ; p < buf+num_read ; ){
			event = (struct inotify_event*) p ; 
			displayInotifyInformation(event); 
			p+= sizeof(struct inotify_event) + event->len ;
		}
	}
	return 0 ; 
}
