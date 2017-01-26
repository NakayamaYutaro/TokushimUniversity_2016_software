#ifndef CLIENT_COMMUNICATOR_H
#define CLIENT_COMMUNICATOR_H

#include "Communicator.hpp"
#include <string.h>
#include <iostream>
#include <sstream>

using namespace std;

class ClientCommunicator : public Communicator {
	private:
		sockaddr_in recv_addr;
		sockaddr_in send_addr;
		string server_ip;
	public:
		ClientCommunicator(
			vector<CustomizedRumba> p_c_rumbas,
			vector<Equipment> p_equipments,
			RunawayRumba p_rumba,
			string ip_addr
		);
		bool handshake();
		void sendData(string msg);
		static void* receiveThread(void* args);
		void startReceiving();
};

ClientCommunicator::ClientCommunicator(
		vector<CustomizedRumba> p_c_rumbas,
		vector<Equipment> p_equipments,
		RunawayRumba p_rumba,
		string ip_addr
	) : Communicator(p_c_rumbas, p_equipments, p_rumba), server_ip(ip_addr) {

	send_sock = socket(AF_INET, SOCK_DGRAM, 0);
	recv_addr.sin_family = AF_INET;
	recv_addr.sin_port = htons(CLIENT_RECV_PORT);
	recv_addr.sin_addr.s_addr = INADDR_ANY;

	recv_sock = socket(AF_INET, SOCK_DGRAM, 0);
	send_addr.sin_family = AF_INET;
	send_addr.sin_port = htons(CLIENT_DEST_PORT);
	send_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());

	bind(recv_sock, (struct sockaddr*)&recv_addr, sizeof(recv_addr));
}

bool ClientCommunicator::handshake() {
	static bool waiting_reply = true;
	
	if( waiting_reply ) {
		stringstream ss;
		ss << "{\"cmd\":\"" << CMD_HANDSHAKE << "\"}";
		socklen_t addrlen = sizeof(send_addr);
		sendto(send_sock, ss.str().c_str(), ss.str().size(), 0, (struct sockaddr*)&(send_addr), addrlen);
		// ハンドシェイクへの応答を待機
		char buf[BUFFER_SIZE];
		memset(buf, 0, sizeof(buf));
		if( (recv(recv_sock, buf, sizeof(buf), 0) > 0) ) {
			string msg = buf;
			picojson::object params = JsonObjectMapper::unmarshal(msg);
			// ハンドシェイクへの応答であれば割り振られたIDを取得
			if( params["cmd"].get<string>() == CMD_HANDSHAKE ) {
				client_id = static_cast<int>( params["ID"].get<double>() );
				cout << "ID: " << client_id << endl;
				waiting_reply = false;
			}
		}
		return false;
	}

	char buf[BUFFER_SIZE];
	memset(buf, 0, sizeof(buf));
	if( (recv(recv_sock, buf, sizeof(buf), 0) > 0) ) {
		string msg = buf;
		picojson::object params = JsonObjectMapper::unmarshal(msg);
		// ゲーム開始の合図であればtrueを返す
		return (params["cmd"].get<string>() == CMD_GAMESTART);
	}
	return false;

}
void ClientCommunicator::sendData(string msg) {
	socklen_t addrlen;
	addrlen = sizeof(send_addr);
	sendto(send_sock, msg.c_str(), msg.size(), 0, (struct sockaddr*)&(send_addr), addrlen);
}
void* ClientCommunicator::receiveThread(void* args) {
	Pack4Thread* arg = static_cast<Pack4Thread*>(args);
	while(true) {
		char buf[BUFFER_SIZE];
		memset(buf, 0, sizeof(buf));

		if( recv(*(arg->p_sock), buf, sizeof(buf), 0) > 0 ) {
			string msg_buf = buf;
			picojson::object params = JsonObjectMapper::unmarshal(msg_buf);

			if( params["cmd"].get<string>() == CMD_DISTRIBUTE_DATA ) {
				pthread_mutex_lock(arg->p_mutex_handler);
				// --- this code same as JsonObjectMapper::setGameState --- //
				picojson::array roomba_data = params["roombas"].get<picojson::array>();
				unsigned int i;
				for(i = 0; i < roomba_data.size(); i++) {
					picojson::array status = roomba_data[i].get<picojson::array>();
					Rumba* rumba = (i != roomba_data.size()-1) ? (Rumba*)( &(arg->p_c_rumbas->at(i)) ) : (Rumba*)arg->p_rumba;
					rumba->setCenterPos( Vector<float>( (float)(status.at(1).get<double>()), (float)(status.at(2).get<double>()) ) );
				}
				picojson::array life_data = params["life"].get<picojson::array>();
				for(i = 0; i < life_data.size(); i++) arg->p_equipments->at(i).setLife( (int)(life_data[i].get<double>()) );
				// --- this code same as JsonObjectMapper::setGameState --- //
				pthread_mutex_unlock(arg->p_mutex_handler);
			}

		}

	}
}
void ClientCommunicator::startReceiving() {
	pthread_mutex_init(&mutex_handler, NULL);
	pthread_create(&thread_handler, NULL, &ClientCommunicator::receiveThread,
		new Pack4Thread(&recv_sock, &c_rumbas, &equipments, &rumba, &mutex_handler)
	);
}
#endif
