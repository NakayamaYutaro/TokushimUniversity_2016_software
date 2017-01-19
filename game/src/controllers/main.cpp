#include <iostream>
#include "../Setting.h"
#include "../utils/Timer.h"
#include "../utils/Tuple.h"
#include "../utils/JsonObjectsMapper.h"
#include "../models/RunawayRumba.h"
#include "../models/CustomizedRumba.h"
#include "../models/ServerCommunicator.h"
#include "../views/GameWindow.h"
#include "../views/StartWindow.h"
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

using namespace std;

int main(int argc, char* argv[]) {

	int i;
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

	// --- 各オブジェクトの初期化 --- //
	for(i = 0; i < 2; i++) equipments.push_back(Equipment(i));
	for(i = 0; i < player_num; i++) {
		c_rumbas.push_back( CustomizedRumba( i*200 , i*200) );
	}

	StartWindow s_window = StartWindow();

	// --- 各クラアントとハンドシェイク --- //
	Communicator* communicator = new ServerCommunicator( c_rumbas, equipments, rumba, player_num-1 );
	while(true) {
		s_window.updateWindow();
		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				SDL_Quit();
				return EXIT_SUCCESS;
			}
		}
		// 全クライアントとハンドシェイク終了でbreak
		if( communicator->handshake() ) break;
	}

	// --- ゲーム開始 --- //
	SDL_Init(SDL_INIT_EVERYTHING);
	GameWindow window = GameWindow(player_num, 2);

	while(!is_finished) {

		// ------- test ------- //
		/*
		cout << JsonObjectMapper::getMsgHandshake() << endl;
		string msg = JsonObjectMapper::getMsgSendGameState(&c_rumbas, &rumba, &equipments);
		cout << msg << endl;

		Tuple<char, picojson::object> tuple = JsonObjectMapper::parseJsonMsg(msg);
		if(tuple.getFst() == 'D') JsonObjectMapper::setGameState(tuple.getSnd(), &c_rumbas, &rumba, &equipments);
		cout << JsonObjectMapper::getMsgHandshake() << endl;
		*/
		// ------- test ------- //


		if(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:				// バツボタンをクリック
					is_finished = true;
					break;
			}
		}

		// 次のフレームの各ルンバの挙動，設備のライフの減算を行う
		rumba.calcSpeedVector(window.getFieldRect(), &equipments, c_rumbas);
		rumba.straight();

		// ゲームの状況をクライアントに送信
		communicator->sendData( JsonObjectMapper::getMsgSendGameState( c_rumbas, rumba, equipments) );

		// ゲームの状況を画面に反映
		window.updateObjects(rumba, c_rumbas, equipments);
		window.updateWindow();

		cout << equipments[0].getLife() << endl;

		// 次のフレームまで待機
		timer.wait2NextFrame();
	}

	SDL_Quit();
	return EXIT_SUCCESS;

}
