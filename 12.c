#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  printf("PID:%d,\nPPID:%d,\nPGID:%d,\nUID:%d,\nGID:%d,\nSID:%d\n",getpid(), getppid(), getpgrp(), getuid(), getgid(), getsid(0));
 return 0;

}
 

