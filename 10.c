#include <unistd.h>
#include <sys/inotify.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define Fail(msg) \
	do {perror(msg); return 1;} while(0);

int main(int argc, char* argv[])
{
	if (argc!=2)
		Fail("Wrong input");
	int inotfd, watchdesc;
	size_t const max_size = sizeof(struct inotify_event) + NAME_MAX + 1; 
	size_t size;
	void * buf;
	uint32_t cookie;
	buf = (void *) malloc(max_size);
	inotfd = inotify_init();
	if (inotfd == -1) Fail("Fail to init\n");
	watchdesc = inotify_add_watch(inotfd,argv[1] , IN_MOVED_FROM | IN_MOVED_TO | IN_CREATE);
	if (watchdesc == -1)
		Fail("Fail to add_watch\n");
	do {
		size = read(inotfd, buf, max_size);
		if ((ssize_t)size == -1)
		Fail("Fail to read\n");
		struct inotify_event *struc = buf;
		switch(struc->mask) {
			case IN_CREATE :
				printf("event: CREATION, name: %s\n", struc->name);
				break;
			case IN_MOVED_FROM :
				cookie = struc->cookie;
				break;
			case IN_MOVED_TO :
				if (struc->cookie != cookie) {
					printf("event: MOVING, name: %s\n", struc->name);
				}
				cookie = 0;
				break;
		}
	} while(1);
	return(0);
}
