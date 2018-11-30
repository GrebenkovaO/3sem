#include <errno.h>
#include <inttypes.h>
#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int flag=1;
void * thread_body(void *arg)
{
	volatile uint64_t *p = arg;
	while (flag) 
	{
		(*p)++;
	}
	return NULL;
}

int main()
{
	pthread_t child_thread;
	uint64_t i=0;
	//create new thread
	if ((errno = thread_create(&child_thread, NULL, thread_body, &i))) {
	 perror("Failed to create thread");
	 return 1;
        }
	//let it run for 1s
	sleep(1);
	//set stop flag
	flag=0;
	//show results
	printf("%" PRIu64 "\n",i);
	return 0;
}
