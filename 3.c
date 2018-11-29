#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int main()
{
	char buffer[1000];
	struct stat structure;
	int fd_read;
	fd_read = open("write.txt", O_RDONLY, 0700);
	if (fd_read == -1) {
		perror("Failed to open\n");
		return (1);
	}
	if (fstat(fd_read, &structure) == -1) {
		perror("stat error");
		return(2);
	}
	printf("Size of file: %ld bytes \n",structure.st_size);
	if (S_ISSOCK(structure.st_mode)) {
		printf("Incorrect type of file: Socket\n");
		return(3);
	}		
	if (S_ISLNK(structure.st_mode)) {
		printf("Incorrect type of file: Symbolic link\n");
		return(4);
	}
	if (S_ISBLK(structure.st_mode)) {
		printf("Incorrect type of file: Block device\n");
		return(5);
	}
	if (S_ISDIR(structure.st_mode)) {
		printf("Incorrect type of file: Directory\n");
		return(6);
	}
	if (S_ISCHR(structure.st_mode)) {
		printf("Incorrect type of file: Character device\n");
		return(7);
	}
	if (S_ISFIFO(structure.st_mode)) {
		printf("Incorrect type of file: FIFO\n");
		return(8);
	}
	if (S_ISREG(structure.st_mode)) {
		printf("Copying is possible\n");
		int fd_wr = open("Write(1).txt", O_WRONLY | O_CREAT | O_TRUNC, 0700);
		if (fd_wr == -1) {
			perror("Failed to open copied file\n");
			return(9);
		}
		int x = 0;
		ssize_t c=0;//already copied
		while (x != 1) {
			ssize_t read_size = read(fd_read, &buffer, sizeof(buffer));
			if (read_size == -1) {
				perror("Failed to read\n");
					return(10);
			}
			if (read_size == 0) {
				x = 1;
			}
			while (c < read_size) {
				ssize_t write_size = write(fd_wr, &buffer + c, read_size - c);
				if (write_size == -1) {
					perror("Failed to write\n");
					return(11);
				}
				c += write_size;
			}
		}
		close(fd_wr);
		close(fd_read);
	}
	return 0;
}

