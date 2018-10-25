#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>



int main()
{
 pid_t child_id=fork();
 if (child_id<0) 
    { 
      perror("Failed to fork");
      return 1;
    }
  if (child_id>0)
    {
      int result;
      wait(&result);
      printf("Parent process:\nPID:%d,\nPPID:%d,\nPGID:%d,\nUID:%d,\nGID:%d,\nSID:%d,\nRESULT:%d \n",getpid(), getppid(), getpgrp(), getuid(), getgid(), getsid(0), result);
    }
  else printf("Child process:\nPID:%d,\nPPID:%d,\nPGID:%d,\nUID:%d,\nGID:%d,\nSID:%d\n",getpid(), getppid(), getpgrp(), getuid(), getgid(), getsid(0));

return 0;

}
