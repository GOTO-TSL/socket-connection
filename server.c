#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_ADDR "127.0.0.1"
#define SERV_PORT 8080

int main(void) {
    int serv_d;
    int bind_result;
    int listen_result;
    struct sockaddr_in serv_addr;

    // socket
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

    printf("waiting for connection...\n");

}