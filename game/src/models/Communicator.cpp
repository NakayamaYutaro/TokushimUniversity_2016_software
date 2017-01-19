#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "../utils/Tuple.h"
#include "../Setting.h"
#include <iostream>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/int.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 2048

using namespace std;

class Communicator {
	protected:
		int send_sock, recv_sock;
		pthread_mutex_t mutex_handler = PTHREAD_MUTEX_INITIALIZER;
		pthread_t thread_handler;
		string buffer;

		LinkedList<CustomizedRumba> c_rumbas;
		LinkedList<Equipment> equipments;
		RunawayRumba  rumba;

	public:
		Communicator(
			LinkedList<CustomizedRumba> p_c_rumbas,
			LinkedList<Equipment> p_equipments,
			RunawayRumba p_rumba
		) : c_rumbas(p_c_rumbas), equipments(p_equipments), rumba(p_rumba) {}

		bool void handshake();
		virtual void sendData();
		Triple< LinkedList<CustomizedRumba>, LinkedList<Equipment>, RunawayRumba > readData();
		virtual void startReceiving();
		virtual void stopReceiving();
		virtual void* receiveThread(void* args)
};

#endif
