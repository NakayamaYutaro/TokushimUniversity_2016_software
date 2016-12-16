#ifndef ServerCommunicator_H
#define ServerCommunicator_H

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <boost/thread.hpp>
#include <unistd.h>
#include <string.h>
#include <cstdio>

class ServerCommunicator{

    private :
        int n1,n2;
        int sock1,sock2;
        char buf[1024];
        pthread_mutex_t mutex;//mutexの宣言
        pthread_mutex_t unlock;
        struct in_addr_t ipaddr;
	 
    public :
        void senddata();
        void senddata2();
        void* receive1_Thread(void*args);
        void* receive2_Thread(void*args);
        bool Wait2Connection();
}

ServerCommunicator::bool wait2Connection() {
    if (listen(sock, 5)< 0) {
    perror("reader: listen");
    close(sock);
    exit(1);
    }
}  

ServerCommunicator::void* receive1_Thread(void* args) {
       pthread_mutex_lock(&mutex);
       memset(buf, 0, sizeof(buf));//メモリのポインタ,セットする値,セットするサイズ
       n1 = read(csock, buf, sizeof(buf));//データ受信
       pthread_mutex_unlock(&mutex);
       sendto(csock,"HELLO",5,0, (struct sockaddr *)&addr, sizeof(addr));
}

ServerCommunicator::void* receive2_Thread(void* args) {
        pthread_mutex_lock(&mutex);
        memset(buf, 0, sizeof(buf));//メモリのポインタ,セットする値,セットするサイズ
        n2 = read(csock, buf, sizeof(buf));//データ受信
        pthread_mutex_unlock(&mutex);
        sendto(csock,"HELLO",5,0, (struct sockaddr *)&addr, sizeof(addr));
}

//sedataはいるのか？疑問
ServerCommunicator::void senddata(){
    sendto(csock,"HELLO",5,0, (struct sockaddr *)&addr, sizeof(addr));
}

#endif
