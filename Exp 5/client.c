#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void main() {
    char buf[100];
    struct sockaddr_in server;
    int SP1, K;
    socklen_t len = sizeof(server);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; // Server's IP address (can be modified for specific IP)
    server.sin_port = 3003;

    // Change: Use SOCK_DGRAM for UDP communication
    SP1 = socket(AF_INET, SOCK_DGRAM, 0);

    while (1) {
        printf("Enter The Message: ");
        fgets(buf, 100, stdin);

        // Change: Use sendto for UDP, specifying server address
        K = sendto(SP1, buf, 100, 0, (struct sockaddr*) &server, len);

        // Change: Use recvfrom for UDP, waiting for server response
        K = recvfrom(SP1, buf, 100, 0, (struct sockaddr*) &server, &len);
  
        printf("\nMessage from Server: %s\n", buf);
    }
}
