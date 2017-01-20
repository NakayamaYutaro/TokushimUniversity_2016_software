#ifndef STRAT_WINDOW_H
#define STRAT_WINDOW_H

#include "Window.h"
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
};

void StartWindow::updateWindow() {
cout << init_time << endl;
cout << difftime(now, init_time) << endl;
cout << difftime(init_time, now) << endl;

	if(!is_changed_pic) {
		now = time(NULL);
		if(difftime(now, init_time) > TIME_SEC_SHOW_TITLE) {
			changeBackground((char*)SCINARIO_IMG_PATH);
		}
	}
	SDL_Flip(window);
}

#endif
