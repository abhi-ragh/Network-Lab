#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

void main() {
    int client, y, x, k = 5, m = 1, p;
    char buffer[1024];
    struct sockaddr_in servAddr;
    socklen_t addrSize;

    // Create socket
    client = socket(PF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Prepare server address structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5600);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));

    // Connect to server
    y = connect(client, (struct sockaddr*)&servAddr, sizeof(servAddr));
    if (y == -1) {
        perror("Error in connection");
        exit(1);
    }

    // Communication loop
    while (k != 0) {
        // Prepare data to send
        if (m <= 5)
            printf("Sending %d\n", m);
        if (m % 2 == 0)
            strcpy(buffer, "frame");
        else {
            strcpy(buffer, "error");
            printf("Packet Loss\n");
            for (p = 1; p <= 3; p++) {
                printf("Waiting for %d seconds\n", p);
            }
            printf("Retransmitting...\n");
            strcpy(buffer, "frame");
            sleep(3);
        }

        // Send data to server
        x = send(client, buffer, 19, 0);
        if (x == -1) {
            perror("Error in sending");
            exit(1);
        } else
            printf("Sent %d\n", m);

        // Receive acknowledgment from server
        int z = recv(client, buffer, 1024, 0);
        if (z == -1) {
            perror("Error in receiving");
            exit(1);
        }

        // Process acknowledgment
        k--;
        m++;

        if (strncmp(buffer, "ack", 3) == 0)
            printf("Acknowledgement received for %d\n", m - 1);
        else
            printf("Ack not received\n");
    }

    // Close the socket
    close(client);
}
