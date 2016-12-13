#ifndef TIMER_H
#define TIMER_H

#include <SDL/SDL.h>
#include <iostream>

class Timer {
	private:
		unsigned int now;
		unsigned int prev;
		unsigned int rest;
	public:
		Timer() { prev = now = SDL_GetTicks(); }
		void sleep() {
			now = SDL_GetTicks();
			rest = now - prev;
			if(rest < TERM_ONE_FRAME_MS) SDL_Delay(rest);
			prev = now;
		}
};

#endif
