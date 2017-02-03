#ifndef WII_INPUT_MANAGER_H
#define WII_INPUT_MANAGER_H

extern "C"{
	#include <libcwiimote/wiimote.h>
	#include <libcwiimote/wiimote_api.h>
	#include <libcwiimote/wiimote_link.h>
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
		void map2Field(int x, int y);

	public :
		Vector<int> getPos();
		WiiInputManager(char* wii_addr);
		void updatePos();
};

WiiInputManager::WiiInputManager(char* wii_addr) {
	wiimote = WIIMOTE_INIT;
	if(wiimote_connect(&wiimote, wii_addr) < 0) exit(1);
	wiimote.mode.acc = 1; //change mode to recieve data from sensor(1).  
	wiimote.mode.ir = 1;	//change mode to recieve data from sensor(2).
}

void WiiInputManager::map2Field(int x1, int y1) {
	position = Vector<int> (
		x1 * GAME_WINDOW_WIDTH / (POINT_X_MAX - POINT_X_MIN),
		y1 * GAME_WINDOW_HEIGHT / (POINT_Y_MAX - POINT_Y_MIN)
	);
}

Vector<int> WiiInputManager::getPos(){
	updatePos();
	return position;
}

void WiiInputManager::updatePos() {

	if(wiimote_is_open(&wiimote)) {
		if(wiimote_update(&wiimote) < 0) wiimote_disconnect(&wiimote);
		map2Field( wiimote.ir1.x, wiimote.ir1.y );
	}

}

#endif
