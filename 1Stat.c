#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>



int main(int argc, char *argv[])
{
    struct stat info;
    int fd;
 
    if(argc != 2)
    {
       printf("Usage: %s <pathname>\n", argv[0]);
       return 1;
    }

    fd = open(argv[1],O_RDONLY);


    if(fd == -1)
    {
        perror("Failed to open");
        close(fd);
        return 2;
    }

    if (fstat(fd, &info) < 0)
    {
        perror("Failed to stat");
        return 3;
    }


    printf("File type:           ");

    switch (info.st_mode & S_IFMT)
    {
    case S_IFBLK:
        printf("block device\n");
        break;
    case S_IFCHR:
        printf("character device\n");
        break;
    case S_IFDIR:
        printf("directory\n");
        break;
    case S_IFIFO:
        printf("FIFO/pipe\n");
        break;
    case S_IFLNK:
        printf("symlink\n");
        break;
    case S_IFREG:
        printf("regular file\n");
        break;
    case S_IFSOCK:
        printf("socket\n");
        break;
    default:
        printf("unknown?\n");
        break;
    }

    printf("File size:          %lld bytes\n",
           (long long) info.st_size);

    printf("Last status change:       %s", ctime(&info.st_ctime));
    printf("Last file access:         %s", ctime(&info.st_atime));
    printf("Last file modification:   %s", ctime(&info.st_mtime));


    return 0;
}





