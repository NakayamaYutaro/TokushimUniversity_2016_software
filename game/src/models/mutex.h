/*mutex.h*/
#ifndef MUTEX_H

#include <iostream>
#include <pthread.h>

#define MUTEX_H

using namespace std;

class mutex {

	private:
	
	int count_1=0;
	int count_2=0;
	pthread_mutex_t mutex; //mutexの宣言

	public:

	void* threadFunction1( void* args );
	void* threadFunction2( void* args );
	void make_thread();


}


void* threadFunction1( void* args )
{
  int i;
  //mutexのlock
  pthread_mutex_lock(&mutex);
  
  // sleepしてその間に変数の書き換えが無いかを確認する
  system( "sleep 3" );
  cout << "count_1 = ";
  for(i=0;i<=10;i++){
    cout << count_1;
    cout << ",";
    count_1++;
  }
  printf("\n");

  //mutexのunlock
  pthread_mutex_unlock(&mutex);
  // sleepしてその間に変数の書き換えが無いかを確認する
  system( "sleep 3" );
  cout << "count_2 = ";
  for(i=0;i<=10;i++){
    cout << count_2;
    cout << ",";
    count_2++;
  }
  printf("\n");
}

void* threadFunction2( void* args )
{
  cout << "thread 2 call1 " << endl;
  pthread_mutex_lock(&mutex);
  // lock中なのでcount_1は変更されない
  count_1=10;
  cout << "thread 2 call2 " << endl;
  pthread_mutex_unlock(&mutex);
  // unlock中なのでcount_2は変更される
  count_2=10;
}

void make_thread() {
  pthread_t thread_1;

  // mutex初期化
  pthread_mutex_init(&mutex, NULL);

  // スレッドの作成
  pthread_create(&thread_1, NULL, threadFunction1, NULL);
  
  // スレッドのjoin
  pthread_join(thread_1,NULL);
  
  // mutexの破棄
  pthread_mutex_destroy(&mutex); 
  return 0;
}
