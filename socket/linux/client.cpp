#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // Bind an ip address and port to a socket
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(54000);
    
    // Connect
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    printf("Connected!\n");
    char send_buf[4096];
    char recv_buf[4096];
    while(true){
        memset(send_buf, 0, 4096);
        memset(recv_buf, 0, 4096);
        printf("Please input your message to server:");
        scanf("%s", send_buf);
        send(sock, send_buf, sizeof(send_buf), 0);
        recv(sock, recv_buf, sizeof(recv_buf), 0);
        printf("Receive a message from server:%s\n", recv_buf);
    }
    close(sock);

}
