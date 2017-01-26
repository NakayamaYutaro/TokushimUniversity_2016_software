#ifndef WINDOW_H
#define WINDOW_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "Panel.hpp"
#include "../Setting.hpp"
#include <iostream>

class Window {
	protected:
		static SDL_Surface* window;
		SDL_Surface* background;
		LinkedList<Panel> panel_list;
		int width;
		int height;
		SDL_Rect win_rect, src_rect;
		void drawBackground() {	SDL_BlitSurface(background, &src_rect, window, &win_rect); } 
	public:
		Window(int w, int h, char* background_path);
		~Window() {
			SDL_FreeSurface(background);
			SDL_FreeSurface(window);
		}
		int getWidth() { return width; }
		int getHeight() { return height; }
		SDL_Rect getWinRect() { return win_rect; }
		virtual void updateWindow() { };
		void changeBackground(char* background_path);
};

SDL_Surface* Window::window = NULL;

Window::Window(int w, int h, char* background_path) : width(w), height(h) {
	if( (window = SDL_SetVideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, 32, SDL_SWSURFACE)) == NULL) {
		std::cerr << "failed to initialize videomode.\n" << std::endl;
		exit(-1);
	}
	background = IMG_Load(background_path);
	if(background == NULL) {
		std::cerr << SDL_GetError() << std::endl;
		std::exit(-1);
	}
	// set game window's size and background size
	win_rect.x = 0; win_rect.y = 0; 
	win_rect.w = width; win_rect.h = height; 
	src_rect.x = 0; src_rect.y = 0; 
	src_rect.w = background->w;
	src_rect.h = background->h;
	// set game window's size and background size
	SDL_BlitSurface(background, &src_rect, window, &win_rect);
}

void Window::changeBackground(char* background_path) {
	SDL_FreeSurface(background);
	if( (window = SDL_SetVideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, 32, SDL_SWSURFACE)) == NULL) {
		std::cerr << "failed to initialize videomode.\n" << std::endl;
		exit(-1);
	}
	background = IMG_Load(background_path);
	if(background == NULL) {
		std::cerr << SDL_GetError() << std::endl;
		std::exit(-1);
	}
	// set game window's size and background size
	win_rect.x = 0; win_rect.y = 0; 
	win_rect.w = width; win_rect.h = height; 
	src_rect.x = 0; src_rect.y = 0; 
	src_rect.w = background->w;
	src_rect.h = background->h;
	// set game window's size and background size
	SDL_BlitSurface(background, &src_rect, window, &win_rect);
}

#endif
