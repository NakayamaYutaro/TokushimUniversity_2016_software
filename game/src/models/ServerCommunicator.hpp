#ifndef SERVER_COMUNICATOR
#define SERVER_COMUNICATOR

#include "Communicator.hpp"
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
		static void* receiveThread(void* args);
};

ServerCommunicator::ServerCommunicator(
		vector<CustomizedRumba> p_c_rumbas,
		vector<Equipment> p_equipments,
		RunawayRumba p_rumba,
		unsigned int arg_client_num
	) : Communicator(p_c_rumbas, p_equipments, p_rumba), client_num(arg_client_num) {

	recv_sock = socket(AF_INET, SOCK_DGRAM, 0);
	send_sock = socket(AF_INET, SOCK_DGRAM, 0);

	recv_addr.sin_family = AF_INET;
	recv_addr.sin_port = htons(SERVER_RECV_PORT);
	recv_addr.sin_addr.s_addr = INADDR_ANY;

	bind(recv_sock, (struct sockaddr*)&recv_addr, sizeof(recv_addr));

	client_id = 0;

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
			stream <<  "{\"cmd\":\"" << CMD_HANDSHAKE << "\",  \"ID\":" << i+1 << " }";
			sendData(tmp_addr, stream.str());
			cout << "Connected from: " << inet_ntoa(tmp_addr.sin_addr) << ':' << ntohs(tmp_addr.sin_port) << '\n' << buf << endl;
		}
	}
	return (clients.size() >= client_num);
}

void* ServerCommunicator::receiveThread(void* args) {
	Pack4Thread* arg = static_cast<Pack4Thread*>(args);
	while(true) {
		char buf[BUFFER_SIZE];
		memset(buf, 0, sizeof(buf));
		if( recv( *(arg->p_sock), buf, sizeof(buf), 0) > 0 ) {
			string tmp_msg = buf;
			picojson::object params = JsonObjectMapper::unmarshal(tmp_msg);
			// クライアントから操作する改造ルンバの位置情報が送られてきたときに更新
			if( params["cmd"].get<string>() == CMD_DISTRIBUTE_DATA ) {
				int c_id = static_cast<int>( params["ID"].get<double>() );
				pthread_mutex_lock(arg->p_mutex_handler);
				arg->p_c_rumbas->at(c_id).setCenterPos(
					Vector<float>(
						static_cast<float>( params["x"].get<double>() ),
						static_cast<float>( params["y"].get<double>() )
					)
				);
				pthread_mutex_unlock(arg->p_mutex_handler);
			}
		}
	}

}

void ServerCommunicator::sendData(sockaddr_in addr, string msg) {
	socklen_t addrlen;
	addrlen = sizeof(addr);
	const void* tmp_msg = msg.c_str();
	sendto(send_sock, tmp_msg, msg.size(), 0, (struct sockaddr*)&(addr), addrlen);
}

void ServerCommunicator::sendData(string msg) {
	for( unsigned int i = 0; i < clients.size(); i++ ) sendData(clients[i], msg);
}

void ServerCommunicator::startReceiving() {
	pthread_mutex_init(&mutex_handler, NULL);
	pthread_create(&thread_handler, NULL, &ServerCommunicator::receiveThread,
		new Pack4Thread(&recv_sock, &c_rumbas, &equipments, &rumba, &mutex_handler)
	);
}

#endif
