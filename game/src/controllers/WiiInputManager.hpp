#ifndef WII_INPUT_MANAGER_H
#define WII_INPUT_MANAGER_H

extern "C"{
	#include <libcwiimote/wiimote.h>
	#include <libcwiimote/wiimote_api.h>
	#include <libcwiimote/wiimote_link.h>
	#include <libcwiimote/wiimote_util.h>
}
#include <stdio.h>
#include <stdlib.h>
#include "../utils/Vector.hpp"
#include "../Setting.hpp"


#define POINT_X_MIN 0
#define POINT_X_MAX 1791
#define POINT_Y_MIN 0
#define POINT_Y_MAX 1272

class WiiInputManager {
	private: 
		Vector<int> position;
		wiimote_t wiimote;
		bool is_server;

	public :
		Vector<int> getPos();
		WiiInputManager(char* wii_addr, bool is_server);
		~WiiInputManager() { wiimote_disconnect(&wiimote); }
		void updatePos();
};

WiiInputManager::WiiInputManager(char* wii_addr, bool server_flag) : is_server(server_flag){
	wiimote = WIIMOTE_INIT;
	if(wiimote_connect(&wiimote, wii_addr) < 0) {
		cerr << "Wii remote cannot connect" << endl;
		exit(1);
	}
	cout << "wii remote connected : " << wii_addr << endl;
	wiimote.mode.acc = 1; //change mode to recieve data from sensor(1).  
	wiimote.mode.ir = 1;	//change mode to recieve data from sensor(2).
	wiimote.led.bits = is_server ? 1 : 2;
}


Vector<int> WiiInputManager::getPos(){
	updatePos();
	return position;
}

void WiiInputManager::updatePos() {
if(wiimote_is_open(&wiimote)) {
	if(wiimote_update(&wiimote) < 0) {
		wiimote_disconnect(&wiimote);
		cerr << "disconnected" << endl;
		exit(1);
	}
	// wiiリモコンからの入力領域と画面上の座標領域が合わないのでマッピングを行う
	position.setVals(
		GAME_WINDOW_WIDTH - wiimote.ir1.x * GAME_WINDOW_WIDTH / (POINT_X_MAX - POINT_X_MIN) + (is_server ? 0 : GAME_WINDOW_WIDTH),
		wiimote.ir1.y * GAME_WINDOW_HEIGHT / (POINT_Y_MAX - POINT_Y_MIN)
	);
	}
}

#endif
