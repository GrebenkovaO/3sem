#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	static const char example[] = "You should do more\n";
	int wr_flag, fd;
	fd = open("write.txt", O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (fd == -1) {
		perror("Failed to open");
		return (1);
	}
	wr_flag = write(fd, example, strlen(example)); //can be mistakes, if write() read not all, should be with while
	if (wr_flag == -1) {
		perror("Failed to write");
		close(fd);
		return 2;
	}
	close(fd);
	return 0;
}

