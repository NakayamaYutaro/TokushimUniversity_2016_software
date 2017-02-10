#ifndef SERVER_COMUNICATOR
#define SERVER_COMUNICATOR

#include "Communicator.hpp"
#include <vector>
#include <sstream>

using namespace std;

class ServerCommunicator : public Communicator {
	private:
		struct sockaddr_in client;	// ゲームをプレイしているクライアントリスト
		unsigned int client_crumba_num;
		sockaddr_in recv_addr;
		char buf[BUFFER_SIZE];
	public:
		ServerCommunicator(
				vector<CustomizedRumba> p_c_rumbas,
				vector<Equipment> p_equipments,
				RunawayRumba p_rumba,
				unsigned int arg_client_crumba_num
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
		unsigned int arg_client_crumba_num
	) : Communicator(p_c_rumbas, p_equipments, p_rumba), client_crumba_num(arg_client_crumba_num) {

	recv_sock = socket(AF_INET, SOCK_DGRAM, 0);
	send_sock = socket(AF_INET, SOCK_DGRAM, 0);

	int unblock_frag = 1;												// 1 ならばノンブロッキングソケット
	ioctl(recv_sock, FIONBIO, &unblock_frag);		// recv_sockをノンブロッキングに設定

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
	if( recvfrom(recv_sock, buf, sizeof(buf), 0, (struct sockaddr*)&tmp_addr, &addrlen) >= 0 ) {
		unsigned int i = 0;
		tmp_addr.sin_port = htons(SERVER_DEST_PORT);
		client = tmp_addr;
		// ID = 改造ルンバのリスト上でクライアントの操作するルンバたちの先頭インデックス
		ostringstream stream;
		stream <<  "{\"cmd\":\"" << CMD_HANDSHAKE << "\",  \"ID\":" << client_crumba_num << " }";
		sendData(stream.str());
		cout << "Connected from: " << inet_ntoa(tmp_addr.sin_addr) << ':' << ntohs(tmp_addr.sin_port) << '\n' << buf << endl;
		return true;
	}
	return false;
}

void* ServerCommunicator::receiveThread(void* args) {
	Pack4Thread* arg = static_cast<Pack4Thread*>(args);
	unsigned int i;
	while(true) {
		char buf[BUFFER_SIZE];
		memset(buf, 0, sizeof(buf));
		if( recv( *(arg->p_sock), buf, sizeof(buf), 0) > 0 ) {
			string tmp_msg = buf;
			picojson::object params = JsonManager::unmarshal(tmp_msg);
			cout << "[log: msg recv]" << buf << endl;
			// クライアントから操作する改造ルンバの位置情報が送られてきたときに更新
			if( params["cmd"].get<string>() == CMD_DISTRIBUTE_DATA ) {
				int c_id = static_cast<int>( params["ID"].get<double>() );
				picojson::array pos_list = params["roombas"].get<picojson::array>();
				pthread_mutex_lock(arg->p_mutex_handler);
				for(i = 0; i < pos_list.size(); i++) {
					arg->p_c_rumbas->at(c_id + i).setCenterPos(
						Vector<float>(
							static_cast<float>( pos_list[i].get<picojson::object>()["x"].get<double>() ),
							static_cast<float>( pos_list[i].get<picojson::object>()["y"].get<double>() )
						)
					);
				}
				pthread_mutex_unlock(arg->p_mutex_handler);
			}
		}
	}

}

void ServerCommunicator::sendData(string msg) {
	socklen_t addrlen;
	addrlen = sizeof(client);
	const void* tmp_msg = msg.c_str();
	//cout << "[log: msg send] " << msg << endl;
	sendto(send_sock, tmp_msg, msg.size(), 0, (struct sockaddr*)&(client), addrlen);
}

void ServerCommunicator::startReceiving() {
	pthread_mutex_init(&mutex_handler, NULL);
	pthread_create(&thread_handler, NULL, &ServerCommunicator::receiveThread,
		new Pack4Thread(&recv_sock, &c_rumbas, &equipments, &rumba, &mutex_handler)
	);
}

#endif
