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
#include <boost/thread.hpp>
#include <pthread.h>
//#include "ServerCommunicator.h"

int main(){

    int sock,csock;
    int loop=1;
    int fromlen;
    pthread_mutex_t mutex;
    //struct in_addr_t ipaddr;
    struct sockaddr_in addr;
    struct sockaddr_in client;
 
    //サーバー側のソケットを作成
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    //サーバー側のアドレス・ポート指定
    addr.sin_family = AF_INET;
    addr.sin_port = htons(22002);
    //addr.sin_addr.s_addr = inet_addr("127.0.0.1");　
    addr.sin_addr.s_addr = INADDR_ANY;
    
/*IP_MULTICAST_IFで特定のネットワークインターフェースを指定するには、そのネットワークインターフェースに設定されたIPアドレスを利用します。今回は127.0.0.1（ローカルホスト）というネットワークイン ターフェースを指定しています。 */

    /*ファイルディスクリプター socket で参照されるソケットに関連するオプションの操作を行う*/
    /* if (setsockopt(sock,
		IPPROTO_IP,
		IP_MULTICAST_IF,
		(char *)&ipaddr, sizeof(ipaddr)) != 0) {
    	perror("setsockopt");
    	return 1;
     }*/


while(loop) {
    pthread_t Thread1, Thread2;
    pthread_mutex_init(&mutex, NULL);// mutex初期化
    
    pthread_create(&Thread1, NULL,receive1_Thread, NULL);//スレッドの作成
    pthread_create(&Thread2, NULL,receive2_Thread, NULL);//スレッドの作成
   
    pthread_join(Thread1,NULL);//スレッドの終了を待つ
    pthread_join(Thread2,NULL);//スレッドの終了を待つ
    
    pthread_mutex_destroy(&mutex); //mutexの破棄

     //通信終了条件をここに書く   
    }      
 close(csock);    
 close(sock);
 return 0;
}

//$ g++ -o smult multicast_server.cpp -lpthread

