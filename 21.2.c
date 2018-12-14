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

int main() {

struct sockaddr_in addr =
{ addr.sin_family = AF_INET,
addr.sin_port = htons (7542),
addr.sin_addr.s_addr = htonl (INADDR_LOOPBACK)};

int s = socket (PF_INET, SOCK_DGRAM, 0);

struct sockaddr_in remote_addr;
socklen_t remote_addr_size = sizeof(remote_addr);
char remote_addr_str[INET_ADDRSTRLEN];
while(1)  {
         
	sendto (s, "Hello World", 12, 0,(const struct sockaddr*) &addr, sizeof (addr));
        sleep(2);
	char data[2048];
        ssize_t data_len = recvfrom(s, data, sizeof(data), 0, (const struct sockaddr *)&remote_addr, &remote_addr_size);
	if (data_len < 0) {
               perror("Failed to receive");
               break;
	}
	if (strcmp(inet_ntop(remote_addr.sin_family, &remote_addr.sin_addr, remote_addr_str, sizeof(remote_addr_str)),"NULL")==0)
               Fail("Failed while inet_ntop");

        printf("received packet from %s:%d, content: '%.*s'\n", remote_addr_str, ntohs(remote_addr.sin_port), (int) data_len, data);

                                  }

close (s);
return 0;}

