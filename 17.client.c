#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int i;
	for(i=0; i<argc; i++) {
		printf("%d '%s'\n", i, argv[i]);
	}
	
	mqd_t mq1 = mq_open(argv[1], O_WRONLY, 0220);
    if (mq1 == (mqd_t) -1) {
	    perror("FAiled to open\n");
	    return 1;
	} 
	unsigned p = (unsigned)*argv[3];
	if (mq_send(mq1, argv[2], strlen(argv[2]), p) == -1) {
		perror("Failed to send");
	}

	mq_close(mq1);
	return 0;
}

