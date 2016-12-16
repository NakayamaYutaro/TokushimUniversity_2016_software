#ifndef Communicator_H
#define Communicator_H

#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Communicator{

 private :
	LinkedList <CustomizedRumba*>;
	RunawayRumba* runaway_runmba;
	pthread_mutex_t receiver_mutex ;
	pthread_mutex_t sender_mutex  ;
	
		
 public : 
	void sendDatatoServer();
	void sendDatatoClient();
	void receiveData();
	void startCommunication(void){}
	void handShake();　
	void lockMutex();
	void unlockedMutex();
    
}


Comminicator::void sendDatatoServer(){
    sendto(sock,"HELLO",5,0, (struct sockaddr *)&addr, sizeof(addr));
}

Comminicator::void sendDatatoClient(){
    sendto(csock,"HELLO",5,0, (struct sockaddr *)&addr, sizeof(addr));
}

Communicator::void receiveData(){
    


}

Communicator::void handShake(){
    bind(sock0, (struct sockaddr *)&addr, sizeof(addr));//server_socketにアドレスを結びつける
    if (listen(sock, 5) < 0) {
        perror("reader: listen");
        close(sockfd);
        exit(1);
    }
}


#endif



