#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
//#include <ClientCommunicator.h>
int main(){
    
    int n;
    /*ーーーーー変数宣言ーーーーー*/
    int csock;
    int server;
    int loop = 1;
    char buf[2048];
    struct sockaddr_in addr;

    /*ーーーーークライアントソケットの作成ーーーーー*/
    csock = socket(AF_INET, SOCK_DGRAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(22002);//no targets in 0-1024
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    /*ーーーーー通信の開始ーーーーー*/
    connect(csock, (struct sockaddr *)&server, sizeof(server));
    
    /*ーーーーーデータ通信ーーーーー*/
    memset(buf, 0, sizeof(buf));//メモリのポインタ,セットする値,セットするサイズ
    n=recv(csock, buf, sizeof(buf), 0);
    printf("%s\n", buf);
    close(csock);
    return 0;
}

/*
UDPポートの複数Bindについて

　ソケットでデータを受信する時ソケットを作成してポート番号をbindするが、そのポート番号が既にbind済である場合エラーとなり出来ない。
　だがUDPの場合、作成したソケットに対しsetsockoptでSO_REUSEADDRを1に設定するとこれが可能になる。ただし、そのソケットからデータを読み取れるのは一番最後にそのポートをbindしたソケットのみとなり、ほかのソケットは読み取り時に待機となる。

　例えば、sock1・sock2・sock3の順でソケットをbindした場合、読み取り可能なソケットはsock3のみとなる。sock3をクローズしない限りsock1・sock2からはデータは読み出せない。たとえsock3で読み取りしていない場合でも、sock3がクローズされない限りsock1・sock2はデータを読み出せない。

　また、読み取り可能なソケットをクローズした場合、次に読み取り可能となるのはクローズしたソケットの直前にbindしたソケットになる。

　例えば、sock1・sock2・sock3の順でソケットをbindした場合、sock3→sock2→sock1の順番でクローズするたびに読み取り可能となる。*/
