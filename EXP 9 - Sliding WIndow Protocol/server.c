#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

void main(){
    int server, newSock, k=5, m=1, p;
    char buffer[1024];

    struct sockaddr_in servAddr;
    struct sockaddr_storage store;

    socklen_t addrSize;

    // Create socket
    server = socket(PF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Prepare server address structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5600);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));

    // Bind socket to address
    if (bind(server, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        perror("Error binding");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server, 5) == 0)
        printf("Listening\n");
    else {
        perror("Error listening");
        exit(1);
    }

    // Accept incoming connection
    addrSize = sizeof(store);
    newSock = accept(server, (struct sockaddr *) &store, &addrSize);
    if (newSock < 0) {
        perror("Error accepting connection");
        exit(1);
    }

    // Communication loop
    while (k != 0) {
        // Receive data from client
        int y = recv(newSock, buffer, 1024, 0);
        if (y == -1) {
            perror("Error in receiving");
            exit(1);
        }

        // Process received data
        if (strncmp(buffer, "frame", 5) == 0)
            printf("Received %d successfully\n", m);
        else
            printf("Frame %d not received\n", m);

        // Determine response (acknowledgment)
        if (m % 2 == 0)
            strcpy(buffer, "ack");
        else {
            strcpy(buffer, "kca");
            printf("Ack lost\n");
            for (p = 1; p <= 3; p++) {
                printf("Waiting for %d seconds\n", p);
            }
            printf("Retransmitting ack...\n");
            strcpy(buffer, "ack");
            sleep(3);
        }
        printf("Sending ack %d...\n", m);

        // Send acknowledgment back to client
        int z = send(newSock, buffer, 19, 0);
        if (z == -1) {
            perror("Error in sending");
            exit(1);
        }

        // Update counters
        k--;
        m++;
    }

    // Close the socket
    close(newSock);
}
