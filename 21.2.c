#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define Fail(msg)\
        do {perror(msg); return 1; } while(0)

int main(int argc, char* argv[]) {
int port;

if (argc==1)
port=7542;
  else if (argc==2)
	  port=(int)atoi(argv[1]);
       else Fail("Wrong input");

struct sockaddr_in addr =
{ addr.sin_family = AF_INET,
addr.sin_port = htons (port)} ;

if (inet_pton(AF_INET,"192.168.0.2", &addr.sin_addr)<1)
      Fail("ОШИБКА");

int s = socket (PF_INET, SOCK_DGRAM, 0);

struct sockaddr_in remote_addr;
socklen_t remote_addr_size = sizeof(remote_addr);
char remote_addr_str[INET_ADDRSTRLEN];
while(1)  {
         

	sendto (s, "YOU is INVALID!!", 16, 0,(struct sockaddr*)&addr, sizeof (addr));
        sleep(2);
	char data[2048];
        ssize_t data_len = recvfrom(s, data, sizeof(data), 0, (const struct sockaddr *)&remote_addr, &remote_addr_size);
	if (data_len < 0) {
               perror("Failed to receive");
               break;
	}
	if (strcmp(inet_ntop(remote_addr.sin_family, &remote_addr.sin_addr, remote_addr_str, sizeof(remote_addr_str)),"NULL")==0)
	{       close(s);
	       	Fail("Failed while inet_ntop");
	}
        printf("received packet from %s:%d, content: '%.*s'\n", remote_addr_str, ntohs(remote_addr.sin_port), (int) data_len, data);
        }
                                  
close (s);
return 0;}

