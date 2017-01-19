#ifndef SERVER_COMUNICATOR
#define SERVER_COMUNICATOR

#include "Communicator.h"
#include <vector>
#include <sstream>

using namespace std;

class ServerCommunicator : public Communicator {
	private:
		vector<struct sockaddr_in> clients;	// ゲームをプレイしているクライアントリスト
		unsigned int client_num;
		sockaddr_in recv_addr;
		char buf[BUFFER_SIZE];
		void sendData(sockaddr_in addr, string msg);
	public:
		ServerCommunicator(
				vector<CustomizedRumba> p_c_rumbas,
				vector<Equipment> p_equipments,
				RunawayRumba p_rumba,
				unsigned int arg_client_num
		);
		Triple< vector<CustomizedRumba>, vector<Equipment>, RunawayRumba > readData();
		bool handshake();
		void sendData(string msg);
		void startReceiving();
		void stopReceiving();
		static void* receiveThread(void* args);
};

ServerCommunicator::ServerCommunicator(
		vector<CustomizedRumba> p_c_rumbas,
		vector<Equipment> p_equipments,
		RunawayRumba p_rumba,
		unsigned int arg_client_num
	) : Communicator(p_c_rumbas, p_equipments, p_rumba), client_num(arg_client_num) {

using namespace std;

	recv_sock = socket(AF_INET, SOCK_DGRAM, 0);
	send_sock = socket(AF_INET, SOCK_DGRAM, 0);

	recv_addr.sin_family = AF_INET;
	recv_addr.sin_port = htons(SERVER_RECV_PORT);
	recv_addr.sin_addr.s_addr = INADDR_ANY;

	bind(recv_sock, (struct sockaddr*)&recv_addr, sizeof(recv_addr));

}

bool ServerCommunicator::handshake() {
	socklen_t addrlen;
	sockaddr_in tmp_addr;

	memset(buf, 0, sizeof(buf));
	addrlen = sizeof(tmp_addr);
	// --- 送信者がclientsに登録されていなければ新規に登録する ---  //
	if( recvfrom(recv_sock, buf, sizeof(buf), 0, (struct sockaddr*)&tmp_addr, &addrlen) >= 0 ) {
		unsigned int i = 0;
		for(; i < clients.size(); i++) {
			if( clients[i].sin_addr.s_addr == tmp_addr.sin_addr.s_addr ) break;
		} 
		if( i == clients.size() ) {
			tmp_addr.sin_port = htons(SERVER_DEST_PORT);
			clients.push_back(tmp_addr);
			// クライアントにIDを返信
			ostringstream stream;
			stream <<  "{\"cmd\":" << i+1 << "}";
			sendData(tmp_addr, stream.str());
			cout << "Connected from: " << inet_ntoa(tmp_addr.sin_addr) << ':' << ntohs(tmp_addr.sin_port) << '\n' << buf << endl;
		}
	}
	return (clients.size() >= client_num);
}

void* ServerCommunicator::receiveThread(void* args) {
	socklen_t addrlen;
	sockaddr_in tmp_addr;

	while(true) {
	}

}

Triple< vector<CustomizedRumba>, vector<Equipment>, RunawayRumba > ServerCommunicator::readData() {
	return Triple< vector<CustomizedRumba>, vector<Equipment>, RunawayRumba >(c_rumbas, equipments, rumba);
}

void ServerCommunicator::sendData(sockaddr_in addr, string msg) {
	socklen_t addrlen;
	addrlen = sizeof(addr);
	const void* tmp_msg = msg.c_str();
	sendto(send_sock, tmp_msg, msg.size(), 0, (struct sockaddr*)&(addr), addrlen);
}

void ServerCommunicator::sendData(string msg) {
	for( unsigned int i = 0; i < clients.size(); i++ ) {
		sendData(clients[i], msg);
	}
}

void ServerCommunicator::startReceiving() {
	pthread_mutex_init( &mutex_handler, NULL );
	pthread_create( &thread_handler, NULL, &receiveThread, NULL );
}
void ServerCommunicator::stopReceiving() {
	pthread_cancel(thread_handler);
	pthread_join(thread_handler, NULL);
}

#endif
