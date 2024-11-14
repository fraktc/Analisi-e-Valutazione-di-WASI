#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <emscripten.h>

#define PORT 8080
#define MESSAGE_SIZE 1024 // Adjust as needed

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[MESSAGE_SIZE];

    // Create the socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure the address/port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    // Accept a connection
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // Message exchange loop
    int start_time = emscripten_get_now();
    int num_messages = 0;
    while (emscripten_get_now() - start_time < 5000) { 
        recv(client_fd, buffer, MESSAGE_SIZE, 0);
        send(client_fd, buffer, MESSAGE_SIZE, 0); 
        num_messages++;
    }

    printf("Number of messages exchanged in 5 seconds: %d\n", num_messages);

    close(client_fd);
    close(server_fd);
    return 0;
}
