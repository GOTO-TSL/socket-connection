#include <stdio.h>
#include <sys/socket.h>

#define SERV_ADDR "127.0.0.1"
#define SERV_PORT 8080

int main(void) {
    int cli_d;
    int connect_result;
    struct sockaddr_in serv_addr;

    // socketの作成
    cli_d = socket(AF_INET, SOCK_STREAM, 0);
    if (cli_d == -1) {
        printf("socket error\n");
        return 0;
    }

    // connection
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = inet_addr(SERV_ADDR);

    connect_result = connect(cli_d, )




}