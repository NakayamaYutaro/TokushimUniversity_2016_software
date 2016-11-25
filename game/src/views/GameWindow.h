#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "Window.h"
#include "../Setting.h"

class GameWindow : public Window {
	private:
	public:
		GameWindow(int h, int w) : Window(h, w, GAME_WINDOW_IMG_PATH) { }
		void drawObjects() {
			// 
		}
};
