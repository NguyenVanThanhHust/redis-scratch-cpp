#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main()
{
    int status, valread, client_fd;
    sockaddr_in server_addr;

    char* message = "hello from client";
    // char* message = "exit";
    char buffer[1024] = {0};
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation error");
        return -1;
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) < 0)
    {
        printf("\n Invalid address/ Address not supported \n");
        return -1;
    }
    
    if ((status = connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0)
    {
        printf("\n Connection failed \n");
        return -1;
    }
    
    send(client_fd, message, strlen(message), 0);
    printf("Message is sent \n");
    valread = read(client_fd, buffer, 1024-1);
    printf("%s \n", buffer);

    close(client_fd);
    return 0;

}