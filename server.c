#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERV_ADDR "127.0.0.1"
#define SERV_PORT 8080
#define BUF_SIZE 1024

int transfer(int);

int transfer(int sock) {
    char recv_buf[BUF_SIZE], send_buf;
    int recv_size, send_size;

    while(1) {

        // recieve client message
        recv_size = recv(sock, &recv_buf, BUF_SIZE, 0);
        if (recv_size ==  -1) {
            printf("recieve error\n");
            break;
        }

        // send response
        if ((strcmp(recv_buf, "finish") == 0) || (recv_size == 0)) {
            printf("finish connection\n");

            send_buf = 1;
            send_size = send(sock, &send_buf, 1, 0);
            if (send_size == -1) {
                printf("send error");
                break;
            }   
            break;
        } else {
            send_buf = 0;
            send_size = send(sock, &send_buf, 1, 0);
            if (send_size == -1) {
                printf("send error");
                break;
            } 
        }
        printf("received:%s\n", recv_buf);
    }

    return 0;
}
/* ここからメイン */
int main(void) {
    int serv_d;
    int cli_d;
    int bind_result;
    int listen_result;
    struct sockaddr_in serv_addr;

    // create socket
    serv_d = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_d == -1) {
        printf("socket error\n");
        return -1;
    }

    printf("socket created\n");

    // bind
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = inet_addr(SERV_ADDR);

    bind_result = bind(serv_d, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (bind_result == -1) {
        printf("bind error\n");
        return -1;
    }

    printf("bind succeeded\n");

    // listen
    listen_result = listen(serv_d, 3);
    if (listen_result == -1) {
        printf("listen error\n");
        return -1;
    }

    while(1) {
        printf("waiting for connection...\n");
        // accept
        cli_d = accept(serv_d, NULL, NULL);
        if (cli_d == -1) {
            printf("accept error\n");
            return -1;
        }

        printf("connecting!\n");

        // data transition
        transfer(cli_d);

        // close client socket
        close(cli_d);

    }

    // close server socket
    close(serv_d);

    return 0;

}