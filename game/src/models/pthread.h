/*semaphore.h
複数のタスクが同一資源にアクセスする上限を規定する時に用いる。*/

#ifndef PTHREAD_H

#include <iostream>
#include <pthread.h>
#include <semaphore.h>

#define PTHREAD_H


sem_t sem;// sem_t型の定義
int count = 0;

void* threadFunction1( void* args )
{
    while(1){
        std::cout << "called threadFunction1" << std::endl;
        std::cout << "count before wait = ";
        std::cout << count << std::endl;
        // 待機状態
        sem_wait( &sem );
        std::cout << "count = ";
        std::cout << count << std::endl;
        count = 0;
    }
    return NULL;
}

/*
void* threadFunction2( void* args )
{
    while(1){
        std::cout << "called threadFunction2" << std::endl;
        std::cout << "count before wait = ";
        std::cout << count << std::endl;
        // 待機状態
        sem_wait( &sem );
        std::cout << "count = ";
        std::cout << count << std::endl;
        count = 0;
    }
    return NULL;
}
*/

int main()
{
    int status;
    pthread_t thread_1, thread_2;
    int n;

    // sempahoreの初期化
    sem_init( &sem, 0, 0 );
    
    // スレッド1個目作成
    status = pthread_create( &thread_1, NULL, threadFunction1, NULL );
    if( status != 0 ) {
        std::cout << "failed to create thread 1" << std::endl;
        exit(1);
    }

    // スレッド2個目作成
    /*
    status = pthread_create( &thread_2, NULL, threadFunction2, NULL );
    if( status != 0 ) {
        std::cout << "failed to create thread 2" << std::endl;
        exit(1);
    }
    */

    // detach 
    pthread_detach( thread_1 );
    //pthread_detach( thread_2 );
    
    for ( n = 0; n < 5; ){
        count++;
        if ( count == 20 ) {
            // semaphoreの値を1加算 シグナル送信
            std::cout << "main count = ";
            std::cout << count << std::endl;
            sem_post( &sem );
            n++;
        }
    }
    
    // semaphore解放
    sem_destroy( &sem );
}
