#ifndef TIMER_H
#define TIMER_H

#include <SDL/SDL.h>
#include <iostream>

class Timer {
	private:
		unsigned int now_p, now_f;
		unsigned int prev_p, prev_f;
		unsigned int rest;
	public:
		Timer() { prev_f = now_f = prev_p = now_p = SDL_GetTicks(); }
		void wait2NextPhysicsCalc() {
			now_p = SDL_GetTicks();
			rest = now_p - prev_p;
			if(rest < PHYSICS_CALC_TERM) SDL_Delay(rest);
			prev_p = now_p;
		}
		bool isWaitedOneFrame() {
			now_f = SDL_GetTicks();
			if( now_f - prev_f >= FRAME_TERM ) {
				prev_f = now_f;
				return true;
			}
			return false;
		}
};

#endif
