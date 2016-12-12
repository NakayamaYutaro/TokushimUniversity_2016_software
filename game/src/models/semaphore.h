/*semaphore.h
複数のタスクが同一資源にアクセスする上限を規定する時に用いる。*/

#ifndef SEMAPHORE_H

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>	
#include <errno.h>		

#define SEMAPHORE_H


class semaphore {

	private :
	
	pthread_t thread_1, thread_2;
	sem_t sem;
	int count = 0;
	int status;
	int n;			
		
	public :
	
	void* thread_Function1( void* args );
	void* thread_Function2( void* args );
	void make_thread();

}


void* thread_Function1( void* args )
{
    while(1){
        std::cout << "called threadFunction1" << std::endl;
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

void makethread() {

    /*アクセス上限の初期化(メモリ空間の確保)*/
    sem_init( &sem, 0, 0 );
    
    /*スレッド1個目作成*/
    status = pthread_create( &thread_1, NULL, makethread, NULL );
    if( status != 0 ) {
        std::cout << "failed to create thread 1" << std::endl;
        exit(1);
    }

    /*スレッド2個目作成*/
    /*
    status = pthread_create( &thread_2, NULL, threadFunction2, NULL );
    if( status != 0 ) {
        std::cout << "failed to create thread 2" << std::endl;
        exit(1);
    }
    */

    // detach(スレッドのメモリ解放の許可)
    pthread_detach( thread_1 );

    
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
    
    // アクセス上限の解放
    sem_destroy( &sem );
}
