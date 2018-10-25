#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <limits.h>

int id(void)
{
  gid_t a[NGROUPS_MAX];
  int i;
  printf("PID:%d,\n",getpid());
  printf("PPID:%d,\n", getppid());
  printf("PGID:%d,\n", getpgrp());
  printf("UID:%d(%s),\n",  getuid(), getpwuid(getuid())->pw_name);
  printf("GID:%d(%s),\n",getgid(), getgrgid(getgid())->gr_name);
  printf("SID:%d,\n",getsid(0));
  printf("EUID:%d(%s),\n",geteuid, getpwuid(geteuid())->pw_name);
  printf("EGID:%d(%s),\n",getegid, getgrgid(getegid())->gr_name);
  printf("GROUPS:\n");
  for  (i=0;i<getgroups(NGROUPS_MAX, a);i++)
      printf("%d(%s)\n",a[i],getgrgid(a[i])->gr_name);
 return 0; 
}

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
      printf("Parent process:\n");
      if (id()!=0)
       {
       perror("Failed to id");
       return 1;
          }
     printf("FINISH STATUS:");
     if (result==0)
        printf("OK");
     else if (WIFEXITED)
        printf("the child terminated normally, that is, by calling exit(3) or _exit(2), or by returning from main()");
          if (WIFSIGNALED)
          {
            printf("the child process was terminated by a signal");
            if (WCOREDUMP)
               printf("the child produced  a  core  dump");
          }
          if (WIFSTOPPED)
              printf("the child process was stopped by delivery of a signal");
          if (WIFCONTINUED)
               printf("the  child  process  was resumed by delivery of SIGCONT");

    }
  else {
         printf("Child process:\n");
         if (id()!=0)
          {
       perror("Failed to id");
       return 1;
          }
       }
}

return 0;

}
