#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

int main()
{
    // Create a socket
    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    
    // Bind an ip address and port to a socket
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(54000);
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // Tell that the socket is for listening
    listen(serv_sock, SOMAXCONN);

    // Wait for a connection
    printf("linux:Waiting for a client.");
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

    char host[NI_MAXHOST];
    char service[NI_MAXHOST];
    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXHOST);
    
    if(getnameinfo((sockaddr*)&clnt_addr, sizeof(clnt_addr), host, NI_MAXHOST, service, NI_MAXHOST, 0) == 0){
        printf("%s connected on port %s\n", host, service);
    }

    // Close listening socket
    close(serv_sock);

    char buf[4096];
    char greeting[] = "This is Linux server, thank you for your meesage!";
    while(true){
        memset(buf, 0, 4096);
        int bytesReceived = recv(clnt_sock, buf, 4096, 0);
        printf("receive a message from client:%s\n", buf);
        if(bytesReceived == SO_ERROR){
            printf("Error in recv()\n");
            break;
        }
        send(clnt_sock, greeting, sizeof(greeting), 0);
    }
    close(clnt_sock);

    return 0;
}
