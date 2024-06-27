#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 15050
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char filename[256];
    FILE *fp;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    printf("Connected to server\n");

    printf("Enter filename to receive: ");
    scanf("%s", filename);
    send(sock, filename, strlen(filename), 0);
    printf("Requested file: %s\n", filename);

    fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int n;
    size_t total_bytes = 0;
    while ((n = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
        if (strcmp(buffer, "File not found") == 0) {
            printf("File not found on server\n");
            break;
        }
        fwrite(buffer, 1, n, fp);
        total_bytes += n;
    }

    fclose(fp);
    close(sock);
    
    if (total_bytes > 0) {
        printf("File received successfully. Total bytes: %zu\n", total_bytes);
    } else {
        printf("No data received. Deleting empty file.\n");
        remove(filename);
    }

    return 0;
}