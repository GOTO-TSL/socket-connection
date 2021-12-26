#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERV_ADDR "127.0.0.1"
#define SERV_PORT 8080
#define BUF_SIZE 1024

int transfer(int sock);

int transfer(int sock) {
    char recv_buf, send_buf[BUF_SIZE];
    int recv_size, send_size;
    while(1) {
        // input message
        printf("Input Message:");
        scanf("%s", send_buf);

        // send message
        send_size = send(sock, &send_buf, strlen(send_buf)+1, 0);

        if (send_size == -1) {
            printf("send error\n");
            break;
        }

        // recieve server response   
        recv_size = recv(sock, &recv_buf, 1, 0);
        if (recv_size == -1) {
            printf("recieve error\n");
            break;
        }

        if (recv_buf == 1) {
            printf("exit!\n");
            break;
        }
    }
    
    return 0;
}
/* ここからメイン */
int main(void) {
    int cli_d;
    int connect_result;
    struct sockaddr_in serv_addr;

    // create socket
    cli_d = socket(AF_INET, SOCK_STREAM, 0);
    if (cli_d == -1) {
        printf("socket error\n");
        return 0;
    }

    printf("socket created\n");

    // connection
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = inet_addr(SERV_ADDR);

    connect_result = connect(cli_d, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (connect_result == -1) {
        printf("connection error\n");
        return -1;
    }

    printf("connected!\n");

    // data transition
    transfer(cli_d);

    // close
    close(cli_d);

    return 0;
}