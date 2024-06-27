#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 15050
#define BUFFER_SIZE 1024

void send_file(FILE *fp, int sockfd) {
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    size_t total_bytes = 0;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
        if (send(sockfd, buffer, bytes_read, 0) < 0) {
            perror("Error sending file");
            return;
        }
        total_bytes += bytes_read;
    }
    printf("Total bytes sent: %zu\n", total_bytes);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char filename[256];
    FILE *fp;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    printf("Server listening on port %d\n", PORT);

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        printf("New connection accepted\n");

        memset(filename, 0, sizeof(filename));
        recv(new_socket, filename, sizeof(filename) - 1, 0);
        printf("Requested file: %s\n", filename);
        
        fp = fopen(filename, "rb");
        if (fp != NULL) {
            printf("File opened successfully\n");
            send_file(fp, new_socket);
            fclose(fp);
        } else {
            perror("Error opening file");
            send(new_socket, "File not found", 14, 0);
        }
        close(new_socket);
        printf("Connection closed\n");
    }
    return 0;
}