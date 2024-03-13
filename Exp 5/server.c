#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void main() {
    char buf[100];
    struct sockaddr_in server, client;
    int SP1, K;
    socklen_t len = sizeof(client);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 3003;

    // Change: Use SOCK_DGRAM for UDP communication
    SP1 = socket(AF_INET, SOCK_DGRAM, 0);
    if (SP1 < 0) {
        perror("socket");
        exit(1);
    }

    // Change: Bind the socket to allow receiving messages
    K = bind(SP1, (struct sockaddr*) &server, sizeof(server));
    if (K < 0) {
        perror("bind");
        exit(1);
    }

    while (1) {
        K = recvfrom(SP1, buf, 100, 0, (struct sockaddr*) &client, &len);
        if (K < 0) {
            perror("recvfrom");
            exit(1);
        }

        printf("\nMessage From Client: %s\n", buf);

        printf("Enter Message to Send:");
        fgets(buf, 100, stdin);

        // Change: Use sendto for UDP, specifying client address
        K = sendto(SP1, buf, 100, 0, (struct sockaddr*) &client, len);
        if (K < 0) {
            perror("sendto");
            exit(1);
        }
    }
}

