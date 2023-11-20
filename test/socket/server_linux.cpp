#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#define PORT 8080

using std::cout;
using std::endl;

int main()
{
    int server_fd, new_socket;
    ssize_t valread;
    sockaddr_in address;

    int opt=1;
    socklen_t  addrlen = sizeof(address);
    char buffer[1024] = {0};
    char* message="Hello from server";

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attaching socket to port 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT); // host ot netshort

    // check if we can bind socket to address and port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    int max_pending_connection = 3;
    if (listen(server_fd, max_pending_connection) < 0)
    {
        perror("listen error");
        exit(EXIT_FAILURE);
    }
    
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen))< 0) {
        perror("accept error");
        exit(EXIT_FAILURE);
    }

    // Receive from clinet
    valread = read(new_socket, buffer, 1024 - 1); // subtract 1 for null terminator at the end
    cout<<buffer<<endl;

    // Send to client 
    send(new_socket, message, strlen(message), 0);
    cout<<"send message to client"<<endl;
    
    // close the connected socket
    close(new_socket);

    // close the listenint socket
    close(server_fd);
    return 0;
}