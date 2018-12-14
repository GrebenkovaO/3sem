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


        //Allocate socket, datagram
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock == -1)
          Fail("Failed to create socket");

        struct sockaddr_in local_addr = {
                .sin_family = AF_INET,
                .sin_port = htons(7542),
                .sin_addr.s_addr = htonl(INADDR_ANY)
        };
        char reply[1024];
	struct sockaddr_in remote_addr;
        socklen_t remote_addr_size = sizeof(remote_addr);
        char remote_addr_str[INET_ADDRSTRLEN];
        socklen_t local_addr_size= sizeof(local_addr);


        if (bind(sock, (const struct sockaddr *)&local_addr, sizeof(local_addr)))
                Fail("Failed to bind"); 

        while(1) {       
       	char data[2048];

		ssize_t data_len = recvfrom(sock, data, sizeof(data), 0, (const struct sockaddr *)&remote_addr, &remote_addr_size);
                if (data_len < 0) {
                        perror("Failed to receive");
                        break;
                                  }
       if (strcmp(inet_ntop(remote_addr.sin_family, &remote_addr.sin_addr, remote_addr_str, sizeof(remote_addr_str)),"NULL")==0)
               Fail("Failed while inet_ntop");

        printf("received packet from %s:%d, content: '%.*s'\n", remote_addr_str, ntohs(remote_addr.sin_port), (int) data_len, data);
        snprintf(reply, sizeof(reply), " Received from %s", remote_addr_str);
        sendto(sock, reply, strlen(reply), 0, (const struct sockaddr *)&remote_addr, remote_addr_size);
	}
close(sock);
return 0;
}
 
