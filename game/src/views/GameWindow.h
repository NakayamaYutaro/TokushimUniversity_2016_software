#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "Window.h"

class GameWindow : public Window {
	public:
		GameWindow(int w, int h) : Window(w, h) { }
		void drawObjects() {
		}
};

#endif
