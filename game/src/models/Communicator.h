#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "../utils/JsonObjectsMapper.h"
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

class Pack4Thread {
	public:
		int* p_sock;
		vector<CustomizedRumba>* p_c_rumbas;
		vector<Equipment>* p_equipments;
		RunawayRumba*  p_rumba;
		pthread_mutex_t* p_mutex_handler;
		Pack4Thread(int* p1, vector<CustomizedRumba>* p2, vector<Equipment>* p3, RunawayRumba* p4, pthread_mutex_t* p5)
		: p_sock(p1), p_c_rumbas(p2), p_equipments(p3), p_rumba(p4), p_mutex_handler(p5) { }
};

class Communicator {
	protected:
		int send_sock, recv_sock;
		int client_id;
		pthread_mutex_t mutex_handler;
		pthread_t thread_handler;

		vector<CustomizedRumba> c_rumbas;
		vector<Equipment> equipments;
		RunawayRumba  rumba;

	public:
		Communicator(
			vector<CustomizedRumba> p_c_rumbas,
			vector<Equipment> p_equipments,
			RunawayRumba p_rumba
		) : c_rumbas(p_c_rumbas), equipments(p_equipments), rumba(p_rumba), mutex_handler(PTHREAD_MUTEX_INITIALIZER) { }

		int getClientID() { return client_id; };
		virtual bool handshake() { return true; };
		virtual void sendData(string msg) {};
		virtual void startReceiving() { cout << "super" << endl; };
		static void* receiveThread(void* args) {};

		Triple< vector<CustomizedRumba>, vector<Equipment>, RunawayRumba > readData(){
			pthread_mutex_lock(&mutex_handler);
			Triple<vector<CustomizedRumba>, vector<Equipment>, RunawayRumba> data = Triple<vector<CustomizedRumba>, vector<Equipment>, RunawayRumba>(c_rumbas, equipments, rumba);
			pthread_mutex_unlock(&mutex_handler);
			return data;
		}
		void stopReceiving() {
			pthread_cancel(thread_handler);
			pthread_join(thread_handler, NULL);
		}
};

#endif
