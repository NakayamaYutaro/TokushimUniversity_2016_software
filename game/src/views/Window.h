#ifndef WINDOW_H
#define WINDOW_H

#include "../utils/LinkedList.h"
#include "Panel.h"
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <iostream>

class Window {
	protected:
		SDL_Surface* window;
		LinkedList<Panel> panel_list;
		char* background_path;
		int width;
		int height;
	public:
		Window(int w, int h, char* img_path) : width(w), height(h), background_path(img_path) {
			width = w;
			height = w;
			if( (window = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE)) == NULL) {
				std::cerr << "failed to initialize videomode.\n" << std::endl;
				exit(-1);
			}
		}
		void drawWindow() { SDL_Flip(window); }
		int getWidth() { return width; }
		int getHeight() { return height; }
};

#endif
