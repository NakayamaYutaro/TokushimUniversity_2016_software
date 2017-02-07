#ifndef RESULT_WINDOW_H
#define RESULT_WINDOW_H

#include "../Setting.hpp"
#include "./Window.hpp"

class ResultWindow : public Window {
	public:
		ResultWindow(bool is_win) : Window(
				GAME_WINDOW_WIDTH,
				GAME_WINDOW_HEIGHT,
				(char*)( is_win ? GAME_WIN_IMG_PATH : GAME_LOSE_IMG_PATH )
		){ }
		void updateWindow() {
			drawBackground();
			SDL_Flip(window);
		}
};

#endif
