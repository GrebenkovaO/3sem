#include <sys/mmap.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	void *p = mmap(
		       NULL,
	               sysconf(_SC_PAGE_SIZE),
	               PROT_READ : PROT_WRITE,
	               MAP_ANONYMOUS : MAP_PRIVATE,
	               -1, // no file
	               0 // offset
		      );
  if  (p== MAP_FAILED) {
   perror("mmap failed");
   return 1;
  }

   printf("New area at address %p\n",p);

 //defined typed pointer
  char *buf = p;
 //write smth to the allocated page 
  strcpy(buf,"Work harder");
 //print page contents
  puts(buf);

return 0;
}
