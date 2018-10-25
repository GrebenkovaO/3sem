#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <limits.h>

int main()
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
 

