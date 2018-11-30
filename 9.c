#include <sys/statvfs.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/vfs.h>
#include <math.h>


int main() {
	struct statfs stat;
	if (statfs(".", &stat))//argv add
 	{
		perror("Failed to statfs\n");
	        return(1);
	}
	printf("Total space: %.1fGB\n",(stat.f_blocks * stat.f_bsize)/1.0e9f);//вывести UID
	printf("Free space: %.1fGb\n", (stat.f_bfree * stat.f_bsize)/1.0e9f);
	return(0);
}

