#ifndef Panel_H

#define Panel_H

#include "../utils/LinkedList.h"
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

class Panel{
	protected:
		SDL_Surface* img;
	public:
		SDL_Rect rect;
		Vector<int> position;
		void drawPanel(SDL_Surface* window) {
		}
}

#endif
