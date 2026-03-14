#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include "ConsolePrintManager.h"

#define PORT 5040 
#define TRUE 1 
#define FALSE 0 
    /*
    Everything on linux is a file. Meaning that it operates with following api: open, read, write and close. 
    Before delving into how we can communicate server software with user or other softwares. we need to understand this api and
    this phrase: everything on linux is a file 
    */

    /*
    We will start with opening a simple file, as we have seen API works flawlessly. 
    And this can be said about sockets too. 
    To create a database server, we need to understand how servers work. server gets a request(usually listening on a port for requests), 
    does stuff with that request and then possibly sends back the data to the user, for instance, web servers send HTTP responses. 
    While database servers return stored data in particular form. 
    
    So now, we shall understand how to create a server generally. 

    I have already defined a PORT on which my server will listen on, that is PORT 5040. Now, to create a communication, we need to understand
    the SOCKET API :

    As manual states, socket "creates an endpoint for communication". it is A Kernel object, a resource, 
    when we create a new socket, file descriptor is returned and we can operate on it via the file descriptor, same API 
    as opening and closing simple files. 

    To understand all this, I will start with simply following my instincts and doing stuff. 
    
    */
int append(int fd, const void* __buf, size_t __n);

int main(int argc, char** argv) { 
    int socket_fd; //listening socket 
    socket_fd = socket(AF_INET, SOCK_STREAM, 0); 
    // new socket is created, supports IPv4 communication 
    // it is a SOCK_STREAM type, that provides reliable two-way
    // connection-based transmition of data(the way we want in database)
    // I write SQL(or my language's) query, database returns data 

    //now as socket is created, we need to name it, it now exists
    //in address family, but has no profession or attributes 
    //we want to give him some names, so we have to fill in the
    //sockaddr struct and pass it to bind as an argument 

    struct sockaddr_in sockaddr;
    sockaddr.sin_port = htons(PORT); //names a socket, tells is on what port to listen to 
    sockaddr.sin_family = AF_INET; //respecified the domain 
    sockaddr.sin_addr.s_addr = INADDR_ANY;

    bind(socket_fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)); 

    //after binding, we now need to listen for requests on this PORT 
    //and accept the request if listen succeeds 
    //name now is Localhost::5040

    listen(socket_fd, 1); //in this case we can have many requests
    //at the same time, or just 1, I am only user currently, so let it
    //be 1 
    //then I accept 
    unsigned int struct_size = sizeof(sockaddr);  
    int accepted_socket_fd = accept(socket_fd, (struct sockaddr*)&sockaddr, &struct_size); 
    //now the communication is open and we can read or write data to user 

    //normal api now works 
    while(TRUE) {
    char buffer[2048]; 
    ssize_t size = read(accepted_socket_fd, buffer, 1024);  
    buffer[size] = 0;
    printf("client sent a message: %s", buffer);
    char* message = malloc(10000); 
    snprintf(message, 10000, "hello user, I got the message!\nHere is your message in red : %s%s%s", getColor("red"), buffer, 
getColor("black")); 
    write(accepted_socket_fd, message, strlen(message)); 
    if(buffer[0] == '0'){
       printf("it was nice serving you!..\n"); 
       break;
    } 
    }
    //we simply read and wrote data back and at last we close both 
    //connections

    close(accepted_socket_fd); 
    close(socket_fd); 
    return 0; 
}


//function appends a file with n bytes from __buf buffer

int append(int fd, const void* __buf, size_t __n) {
    char buffer[2048];
    read(fd, buffer, 2048);
    printf("buffer is: %s\n", buffer); 
    return write(fd, __buf, strlen(__buf)); 
}