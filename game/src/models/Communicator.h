#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "../utils/Tuple.h"
#include "../Setting.h"
#include <iostream>
#include <vector>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 2048

using namespace std;

class Communicator {
	protected:
		int send_sock, recv_sock;
		pthread_mutex_t mutex_handler = PTHREAD_MUTEX_INITIALIZER;
		pthread_t thread_handler;

		vector<CustomizedRumba> c_rumbas;
		vector<Equipment> equipments;
		RunawayRumba  rumba;

	public:
		Communicator(
			vector<CustomizedRumba> p_c_rumbas,
			vector<Equipment> p_equipments,
			RunawayRumba p_rumba
		) : c_rumbas(p_c_rumbas), equipments(p_equipments), rumba(p_rumba) {}

		virtual bool handshake() { return true; };
		virtual void sendData(string msg) {};
		virtual Triple< vector<CustomizedRumba>, vector<Equipment>, RunawayRumba > readData(){
			return Triple< vector<CustomizedRumba>, vector<Equipment>, RunawayRumba >(c_rumbas, equipments, rumba);
		};
		virtual void startReceiving() {};
		virtual void stopReceiving() {};
};

#endif
