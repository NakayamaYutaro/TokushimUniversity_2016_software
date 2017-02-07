#include "../Setting.hpp"
#include "../utils/Timer.hpp"
#include "../utils/Tuple.hpp"
#include "../utils/JsonManager.hpp"
#include "../models/RunawayRumba.hpp"
#include "../models/CustomizedRumba.hpp"
#include "../models/ServerCommunicator.hpp"
#include "../models/ClientCommunicator.hpp"
#include "../views/StartWindow.hpp"
#include "../views/GameWindow.hpp"
#include "../views/ResultWindow.hpp"
#include "./WiiInputManager.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

using namespace std;

void quitGame(Window* window) {
	delete window;
	TTF_Quit();
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

void quitMightClickedQuit(SDL_Event* event, Window* window) {
	if(SDL_PollEvent(event) && event->type == SDL_QUIT) {
		quitGame(window);
	}
}

int main(int argc, char* argv[]) {

	unsigned int i;
	int client_id = 0;
	unsigned int player_num = 2;
	int client_wii_num = 1;
	bool is_finished = false;
	bool is_server = false;
	string ip_address = "127.0.0.1";
	vector<WiiInputManager> wii_list;
	Timer timer = Timer();
	SDL_Event event;

	vector<CustomizedRumba> c_rumbas;
	vector<Equipment> equipments;
	RunawayRumba rumba = RunawayRumba( GAME_WINDOW_WIDTH/2 , GAME_WINDOW_HEIGHT/2);

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_WM_SetCaption(GAME_TITLE, NULL);

	if(argc < 4) {								 // コマンドライン引数のバリデーション
		cerr << "Arguments are not enough!!\n(least 3 args)" << endl;
		exit(1);
	}
	is_server = (argv[1][0] == 'S' || argv[1][0] == 's');
	if(is_server) { player_num = atoi(argv[2]); }
	else { ip_address = argv[2]; }								// クライアントならサーバのIPアドレスを取得

	cout << "start game as a " << (is_server ? "server" : "client") << "!" << endl;

	// --- 各オブジェクトの初期化 --- //
	for(i = 0; i < 2; i++) equipments.push_back(Equipment(i));
	for(i = 0; i < player_num; i++) c_rumbas.push_back( CustomizedRumba( (i+1)*400 , (i+1)*400) );

	StartWindow* s_window = new StartWindow();
	
	Communicator* communicator;
	if(is_server)  communicator = new ServerCommunicator( c_rumbas, equipments, rumba, 2 );
	else communicator = new ClientCommunicator( c_rumbas, equipments, rumba, ip_address );

	s_window->updateWindow();
	// Wiiリモコンの準備
	for(i = 3; i < argc; i++) wii_list.push_back( WiiInputManager(argv[i], is_server) );

	// --- サーバ，クライアントでハンドシェイク --- //
	while(true) {
		s_window->updateWindow();
		quitMightClickedQuit(&event, s_window);
		if( communicator->handshake() ) break;	// ハンドシェイク終了でbreak
	}
	if(is_server) communicator->sendData("{\"cmd\":\"S\"}");

	client_id = communicator->getClientID();

	delete s_window;

	// --- ゲーム開始 --- //
	GameWindow* window = new GameWindow(client_id, player_num, 2);

	// フィールド状況のデータ受信の開始
	communicator->startReceiving();

	while(!is_finished) {

		quitMightClickedQuit(&event, window);

		for(i = client_id; i < wii_list.size(); i++) c_rumbas[i].setCenterPos( wii_list[i-client_id].getPos() );

		if(is_server) {
			// 次のフレームの各ルンバの挙動，設備のライフの減算を行う
			rumba.calcSpeedVector(window->getFieldRect(), &equipments, c_rumbas);
			rumba.straight();
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

		if( timer.isWaitedOneFrame() ) {
			// ゲームの状況を画面に反映
			window->updateObjects(rumba, c_rumbas, equipments);
			window->updateWindow();
		}

		// どちらかのライフが0になればゲームを終了
		for( i = 0; i < equipments.size(); i++ ) {
			if( equipments[i].getLife() <= 0 ) {
				is_finished = true;
			}
		}

		// 次のフレームまで待機
		timer.wait2NextPhysicsCalc();
	}
	delete window;

	ResultWindow* r_window = new ResultWindow( equipments[client_id].getLife() > 0 );
	r_window->updateWindow();
	while(true) {
		quitMightClickedQuit(&event, r_window);
	}

	return EXIT_SUCCESS;

}
