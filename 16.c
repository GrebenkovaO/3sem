#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <pwd.h>
#include <limits.h>
#include <grp.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main()

{
	struct mq_attr c;
	mqd_t mq1 = mq_open("/Q1", O_RDWR | O_CREAT, 0700);
	if (mq1 == -1) {
		perror("Failed to open");
		return(1);
	}
	if (mq_getattr(mq1, &c) == -1) {
		perror("Failed in  mq_getattr");
		}
       	else {
		printf("Stats by mq_getattr:\n");
		printf("MQ_flags = %ld\n", c.mq_flags);
		printf("MQ_maxmsg = %ld\n", c.mq_maxmsg);
		printf("MQ_msgsize = %ld\n", c.mq_msgsize);
		printf("MQ_curmsgs = %ld\n", c.mq_curmsgs);
	}
	mq_close(mq1);
	mq_unlink("/Q1");
	return (0);
}
