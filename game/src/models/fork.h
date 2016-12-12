/* fork.h */
#ifndef FORK_H

#include <iostream>
#include <sys/wait.h>
#include <sys/shm.h>
#include <thread>

#define FORK_H

class mutex {
	
	private:	
	int status;
	int shmid;
	int *shmaddr;

	public:
	void makeprocesses();
	void shm_attach();//share_memory_attach
	void shm_detach();//share_memory_detach 
	void system_exit();
			
}

/*単純なforkではParent/Childプロセス間でデータの共有が出来ないので、共有メモリを介してデータを共有する必要がある。共有メモリを扱うには#include<sys/shm.h>を読み込む必要がある。shm関数*/

void mutex::makeprocesses() {
	
	int count = 0;

	count++;
	std::cout << "カウント数 = ";
	std::cout << count << std::endl;
	pid_t pid;

	pid = fork();//make a child process.

	if((shmid = shmget(IPC_PRIVATE,100,0600)) == -1){//make a sharing memory seg..
		perror("shmget error.");
		exit(exit_failure);
	}
	

	if(pid < 0) {
		std::cout << "forkシステムコールに失敗しました。" << std::endl;
		return 0;

	} else if(pid == 0) {
		putchar('\n');
		std::cout << "子プロセスを作りました. pid = ";
		std::cout << getpid() << std::endl;//get process_id of Child.
		std::cout << "親プロセスのpid =";
		std::cout << pid << std::endl;
		count++;

		shm_attach();
		shm_detach();
		
		exit(EXIT_SUCCESS);

	} else {
		putchar('\n');
		std::cout << "親プロセスを作りました。 pid = ";
		std::cout << getpid() << std::endl;
		std::cout << pid << std::endl;
		count++;

		waitpid( pid, &status, 0 );//Child Processが終わるのを待つ
		std::cout << "終了したプロセス = ";
		std::cout << pid << std::endl;
	}
	
	std::cout << "カウント数 = ";
	std::cout << count << std::endl;
	putchar('\n');
	return 0;
}

void mutex::shm_attach(/*ear*/) {
	if((shmaddr = (int *)shmat(shmid,NULL,0))==(void *)-1){
		perror("子プロセスの共有に失敗しました。");
		exit(EXIT_FAILURE);
	}

	*shmaddr = count;	
	std::cout << "アタッチ数 = ";
	std::cout << *shmaddr << std::endl;
}

void mutex::shm_detach(/*ear*/) {
	if(shmdt(shmaddr)== -1){	
		perror("子プロセスの共有停止に失敗しました。");
		exit(exit_failure);
	}
}

void mutex::system_exit() {//プロセスの終了状態
	if(WIFEXITED(status)){
		printf("exit %d\n",WEXITSTATUS(status));
	}else if(WIFSIGNALED(status)){
		printf("signal %d\n",WTERMSIG(status));
	}else {
		printf("abnormal exit\n");
	}
}
		
}


#endif
