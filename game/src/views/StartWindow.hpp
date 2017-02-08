#ifndef STRAT_WINDOW_H
#define STRAT_WINDOW_H

#include "Window.hpp"
#include <time.h>

#include <iostream>
using namespace std;

class StartWindow : public Window {
	private:
		SDL_Rect field_rect;
		time_t init_time, now;
		bool is_changed_pic;
	public:
		StartWindow() : Window(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, (char*)TITLE_IMG_PATH) { is_changed_pic = false; init_time = time(NULL); }
		void updateWindow();
		void drawBackground();
};

void StartWindow::updateWindow() {

	if(!is_changed_pic) {
		now = time(NULL);
		if(difftime(now, init_time) > TIME_SEC_SHOW_TITLE) {
			changeBackground((char*)SCINARIO_IMG_PATH);
		}
	}
	SDL_Flip(window);

}

void StartWindow::drawBackground() {
	static bool is_initialized = false;
	if(is_initialized) return;
	Window::drawBackground();
	is_initialized = true;
}

#endif
