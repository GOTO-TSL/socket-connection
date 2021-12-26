#include <sys/socket.h>

// reference: https://linuxjm.osdn.jp/html/LDP_man-pages/man2/bind.2.html

// socket(): ソケット通信を行うためにはまずソケットが必要　ソケットを作成する関数
// domain: プロトコルファミリー(アドレスファミリー)を指定
// type: ソケットのタイプを指定
// protocol: 使用するプロトコルを指定
int socket(int domain, int type, int protocol);

// bind(): ソケットにIPアドレスやポート番号を設定する　ソケットの作成後に行う　主にサーバー側
// sockfd: ソケット
// addr: ソケットに割り当てるアドレスやポート番号の情報
// addrlen: addrのサイズ(バイト数)
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

// listen(): ソケットが接続待ち状態になり，connectによる接続要求が可能になる　バインド後にサーバーが行う
// sockfd: 接続を待つソケット
// backlog: 接続要求を保持する数 作成するキューのサイズ
int listen(int sockfd, int backlog);

// connect(): 接続先サーバーのIPアドレスやポート番号を指定　ソケット作成後にクライアントが実行
// sockfd: 接続を行うソケット
// addr: 接続先(アドレスやポート番号など)の情報
// addrlen: addrのサイズ(バイト数)
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

// accept(): サーバー側が接続の受け付けを行う　これによって接続が確立されてその後のデータのやり取りを行うことが出来るようになる
// 接続要求(クライアント側からconnect)が来るまでは関数が終了しない
// 関数内でソケットを作成し，戻り値が作成したソケットの識別子になる　これが接続済みのソケットになる
// sockfd: 接続待ちを行っているソケット　listenで接続待ちになっているソケット
// addr: 接続先の情報へのポインタ
// addrlen: addrのサイズ(バイト数)へのポインタ
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

// send(): データのやり取りを行う　接続先に対してデータを送信する　戻り値は実際に接続先に送信したデータのバイト数
// sockfd: 接続済みのソケット
// buf: 送信するデータへのポインタ
// len: 送信するデータのサイズ(バイト数)
// flags: 送信時の動作の詳細設定
ssize_t send(int sockfd, const void *buf, size_t len, int flags);

// recv(): 接続先が送信したデータを受信する関数　戻り値は実際に接続先から受信したデータのバイト数
// データが到着するまで待ち続ける関数 sendで送信したデータをrecvで受信することを繰り返してやり取りする
// 実行するタイミングに気を付ける必要がある
// sockfd: 接続済みのソケット
// buf: 受信データを格納するバッファのアドレス
// len: bufのサイズ(バイト数)
// flags: 受信時の動作の詳細設定 
ssize_t recv(int sockfd, const void *buf, size_t len, int flags);

// close(): 接続を閉じる　一連の通信処理が終了する
// fd: ソケットの識別子
int close(int sockfd);


