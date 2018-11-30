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
	int result=0;
	struct stat structure;
	int fd_read;
	fd_read = open("write.txt", O_RDONLY);
	if (fd_read == -1) {
		perror("Failed to open\n");
		result=1;
	}
	else if (fstat(fd_read, &structure) == -1) {
		perror("stat error");
	        result=2;
	}
	printf("Size of file: %ld bytes \n",structure.st_size);
	if (S_ISSOCK(structure.st_mode)) {
		printf("Incorrect type of file: Socket\n");
		result=3;
	}
        else if (S_ISLNK(structure.st_mode)) {
		printf("Incorrect type of file: Symbolic link\n");
		result=4;
	}
	else if (S_ISBLK(structure.st_mode)) {
		printf("Incorrect type of file: Block device\n");
		result=5;
	}
	else if (S_ISDIR(structure.st_mode)) {
		printf("Incorrect type of file: Directory\n");
		result=6;
	}
	else if (S_ISCHR(structure.st_mode)) {
		printf("Incorrect type of file: Character device\n");
		result=7;
	}
	else if (S_ISFIFO(structure.st_mode)) {
		printf("Incorrect type of file: FIFO\n");
		result=8;
	}
	else if (S_ISREG(structure.st_mode)) {
		printf("Copying is possible\n");
		int fd_wr = open("Write(1).txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
		if (fd_wr == -1) {
			perror("Failed to open copied file\n");
			result=9;
			return(result);
		}
		int x = 0; //flag
			while (x != 1) {
			ssize_t c = 0;//already copied	
			ssize_t read_size = read(fd_read, buffer, sizeof(buffer));
			if (read_size == -1) {
				perror("Failed to read\n");
					result=10;
				break;
			}
			if (read_size == 0) {
				x = 1;
				break;
			}
			while (c < read_size) {
				ssize_t write_size = write(fd_wr, buffer + c, read_size - c);
				if (write_size == -1) {
					perror("Failed to write\n");
					result=11;
					break;
				}
				c += write_size;
			}
		}
		close(fd_wr);
		close(fd_read);
	}
	return (result);
}

