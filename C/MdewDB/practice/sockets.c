#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 5040 


int main(int argc, char** argv) { 
    int server_fd, new_socket;


    ssize_t valread; 



    struct sockaddr_in address; 



    int opt = 1; 
    socklen_t addrlen = sizeof(address); 
    char buffer[1024] = { 0 };     
    colorTheText("green"); 
    printf("Welcome to MdewDB!\n"); 
    colorTheText("black"); 
    char* hello = "Welcome to MDewDB!\n"; 


    server_fd = socket(AF_INET, SOCK_STREAM, 0); 


    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR
    , &opt, sizeof(opt)); 

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT); 

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    printf("here server starts listening..\n");
    listen(server_fd, 3);
    printf("well, it seems server passed the listen phase...\n"); 
    new_socket = accept(server_fd, (struct sockaddr*)&address,&addrlen);
    printf("here possibly, server has accepted the request and now new socket is created for this communication...\n");
    while(1) { 
    valread = read(new_socket, buffer, 1024 - 1); 
    printf("well if we are here, then it seems we are stopping here, and at read, we wait for the client to pass data to buffer...\n");
    printf("this is the data obtained: %s\n", buffer); 
    if(buffer[0] == '0') {
   	close(new_socket); 
	printf("connection has been closed successfully!\n");
	printf("great serving you!..\n");
	break;
    }
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n"); 
    }    
    close(server_fd); 
    return 0; 
}