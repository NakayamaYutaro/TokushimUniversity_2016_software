#ifndef Panel_H
#define Panel_H

#include "../utils/LinkedList.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>

class Panel{
	protected:
		SDL_Surface* img;
		SDL_Rect img_rect;
		Vector<int> position;
	public:
		Panel(Vector<int> initial_pos, const char* img_path) : position(initial_pos) {
			img = IMG_Load(img_path);
			if(img == NULL) {
				std::cerr << SDL_GetError() << std::endl;
				std::exit(0);
			}
			img_rect.x = 0;
			img_rect.y = 0;
			img_rect.w = img->w;
			img_rect.h = img->h;
		}
		// if client_id == 0 then draw left side, otherwise draw right side
		void drawPanel(SDL_Surface* window, int client_id) {
			SDL_Rect dest_rect;
			dest_rect.x = position.getX() - (GAME_WINDOW_WIDTH*client_id);
			dest_rect.y = position.getY();
			dest_rect.w = img->w;
			dest_rect.h = img->h;
			SDL_BlitSurface(img, &img_rect, window, &dest_rect);
		}
		void setPosition(Vector<int> new_pos) { position = new_pos; }
};

#endif
