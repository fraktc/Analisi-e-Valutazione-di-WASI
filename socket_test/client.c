#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <emscripten.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define MESSAGE_SIZE 1024 // Adjust as needed

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char *message = malloc(MESSAGE_SIZE);
    memset(message, 'a', MESSAGE_SIZE); // Sample data

    // Create the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure the address/port
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    servaddr.sin_port = htons(PORT);

    // Connect
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Message exchange loop
    int start_time = emscripten_get_now();
    int num_messages = 0;
    while (emscripten_get_now() - start_time < 5000) {
        send(sockfd, message, MESSAGE_SIZE, 0);
        recv(sockfd, message, MESSAGE_SIZE, 0);
        num_messages++;
    }

    printf("Number of messages exchanged in 5 seconds: %d\n", num_messages);

    close(sockfd);
    free(message);
    return 0;
}
