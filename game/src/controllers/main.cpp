#include <iostream>
#include <sstream>
#include "../Setting.h"
#include "../utils/Timer.h"
#include "../utils/Tuple.h"
#include "../utils/JsonObjectsMapper.h"
#include "../models/RunawayRumba.h"
#include "../models/CustomizedRumba.h"
#include "../models/ServerCommunicator.h"
#include "../models/ClientCommunicator.h"
#include "../views/GameWindow.h"
#include "../views/StartWindow.h"
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

using namespace std;

int main(int argc, char* argv[]) {

	int i;
	int client_id = 0;
	int player_num = 2;
	bool is_finished = false;
	bool is_server = false;
	string ip_address = "127.0.0.1";
	Timer timer = Timer();
	SDL_Event event;

	vector<CustomizedRumba> c_rumbas;
	vector<Equipment> equipments;
	RunawayRumba rumba = RunawayRumba( GAME_WINDOW_WIDTH/2 , GAME_WINDOW_HEIGHT/2);

	// --- コマンドライン引数のバリデーション --- //
	if(argc < 3) {
		cerr << "Arguments are not enough!!\n(least 3 args)" << endl;
		exit(1);
	}
	is_server = (argv[1][0] == 'S');
	if(is_server) { player_num = atoi(argv[2]); }
	else { ip_address = argv[2]; }

	cout << "start game as a " << (is_server ? "server" : "client") << "!" << endl;

	// --- 各オブジェクトの初期化 --- //
	for(i = 0; i < 2; i++) equipments.push_back(Equipment(i));
	for(i = 0; i < player_num; i++) {
		c_rumbas.push_back( CustomizedRumba( i*200 , i*200) );
	}

	StartWindow s_window = StartWindow();
	
	Communicator* communicator;
	if(is_server)  communicator = new ServerCommunicator( c_rumbas, equipments, rumba, player_num-1 );
	else communicator = new ClientCommunicator( c_rumbas, equipments, rumba, ip_address );

	// --- サーバ，クライアントでハンドシェイク --- //
	while(true) {
		s_window.updateWindow();
		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				SDL_Quit();
				return EXIT_SUCCESS;
			}
		}
		// ハンドシェイク終了でbreak
		if( communicator->handshake() ) break;
	}
	if(is_server) communicator->sendData("{\"cmd\":\"S\"}");

	client_id = communicator->getClientID();

	// --- ゲーム開始 --- //
	SDL_Init(SDL_INIT_EVERYTHING);
	GameWindow window = GameWindow(player_num, 2);

	// フィールド状況のデータ受信の開始
	communicator->startReceiving();

	while(!is_finished) {

		if(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:				// バツボタンをクリック
					is_finished = true;
					break;
			}
		}

		if(is_server) {
			// 次のフレームの各ルンバの挙動，設備のライフの減算を行う
			rumba.calcSpeedVector(window.getFieldRect(), &equipments, c_rumbas);
			rumba.straight();
		}

		if(is_server) {
			// ゲームの状況をクライアントに送信
			communicator->sendData( JsonObjectMapper::getMsgSendGameState( c_rumbas, rumba, equipments) );
		} else {
			// 自分の操作する改造ルンバの位置情報をサーバに送信
			communicator->sendData( JsonObjectMapper::getMyRoombaMsg(client_id, c_rumbas[client_id]) );
		}

		// --- 自分以外のルンバなどのデータを反映 --- //
		Triple< vector<CustomizedRumba>, vector<Equipment>, RunawayRumba > triple = communicator->readData();
		CustomizedRumba tmp = c_rumbas[client_id];
		c_rumbas = triple.getFst();
		c_rumbas[client_id] = tmp;
		if(!is_server) {
			equipments = triple.getSnd();
			rumba = triple.getThrd();
		}
		// --- 自分以外のルンバなどのデータを反映 --- //

		// ゲームの状況を画面に反映
		window.updateObjects(rumba, c_rumbas, equipments);
		window.updateWindow();

		// 次のフレームまで待機
		timer.wait2NextFrame();
	}

	SDL_Quit();
	return EXIT_SUCCESS;

}
