#ifndef SERVER_COMUNICATOR
#define SERVER_COMUNICATOR

#include "./Communicator.h"
#include <vector>

class ServerCommunicator : public {
	private:
		vector<struct sockaddr_in> clients;	// ゲームをプレイしているクライアントリスト
		int client_num;
		addr_in recv_addr
		char buff[BUFFER_SIZE];
	public:
};

ServerCommunicator::ServerCommunicator(
		LinkedList<CustomizedRumba> p_c_rumbas,
		LinkedList<Equipment> p_equipments,
		RunawayRumba p_rumba,
		int arg_client_num
) : Communicator(p_c_rumbas, p_equipments, p_rumba), client_num(arg_client_num){

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	recv_addr.sin_family = AF_INET;
	recv_addr.sin_port = htons(SERVER_RECV_PORT);
	recv_addr.sin_addr.s_addr = INADDR_ANY;

	bind(sock, (struct sockaddr*)&recv_addr, sizeof(recv_addr));

}

bool ServerCommunicator::handshake() {
	socklen_t addrlen;
	sockaddr_in tmp_addr;

	memset(buf, 0, sizeof(buf));
	addrlen = sizeof(tmp_addr);
	// --- 送信者がclientsに登録されていなければ新規に登録する ---  //
	if( recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&tmp_addr, &addrlen) >= 0 ) {
		int i = 0;
		for(; i < clients.size(); i++) {
			if( clients[i].sin_addr.s_addr == tmp_addr.sin_addr.s_addr ) break;
		} 
		if( i == clients.size() ) {
			tmp_addr.sin_port = htons(SERVER_DEST_PORT);
			clients.push_back(tmp_addr);
			cout << "Connected from: " << inet_ntoa(tmp_adr.sin_addr) << ':' << ntohs(tmp_addr.sin_port) << '\n' << buf << endl;
		}
	}
	return clients.size() < client_num;
}

void* ServerCommunicator::receiveThread(void* args) {
	sockeln_t addrlen;
	sockaddr_in tmp_addr;

	while(true) {
	}

}

Triple< LinkedList<CustomizedRumba>, LinkedList<Equipment>, RunawayRumba > ServerCommunicator::readData() {
	return Triple< LinkedList<CustomizedRumba>, LinkedList<Equipment>, RunawayRumba >(c_rumbas, equipments, rumba);
}

void ServerCommunicator::sendData() {
	pthread_mutex_lock(&mutex_handler);
	// 送信メッセージの取得
	string msg = "message";
	pthread_mutex_unlock(&mutex_handler);
	for( int i = 0; i < clients.size(); i++ ) {
		addrlen = sizeof(clients[i]);
		const void* tmp_msg = msg.c_str();
		sendto(sock, tmp_msg, msg.size(), 0, (struct sockaddr*)&(clients[i]), addrlen);
	}
}

void ServerCommunicator::startReceiving() {
	pthread_mutex_init( &mutex_handler, NULL );
	pthread_create( &thread_handler, NULL, &recv_thread, NULL );
}
void ServerCommunicator::stopReceiving() {
	pthread_cancel(handler);
	pthread_join(handler, NULL);
	close(sock);
}

#endif
