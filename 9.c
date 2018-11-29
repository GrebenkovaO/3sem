#include <sys/statvfs.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/vfs.h>
#include <math.h>


int main() {
	struct statfs stat;
	if (statfs(".", &stat))
 	{
		perror("Failed to statfs\n");
	        return(1);
	}
	printf("Total space: %luGB\n",(stat.f_blocks * stat.f_bsize) >> 30);
	printf("Free space: %luGb\n", (stat.f_bfree * stat.f_bsize) >> 30);
	return(0);
}

