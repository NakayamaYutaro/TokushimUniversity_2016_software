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
		Panel(int x, int y, const char* img_path) : position(Vector<int>(x, y)) {
			img = IMG_Load(img_path);
			if(img == NULL) {
				std::cout << SDL_GetError() << std::endl;
				std::exit(0);
			}
			img_rect.x = 0;
			img_rect.y = 0;
			img_rect.w = img->w;
			img_rect.h = img->h;
		}
		void drawPanel(SDL_Surface* window) {
			SDL_Rect dest_rect;
			dest_rect.x = position.getX();
			dest_rect.y = position.getY();
			SDL_BlitSurface(img, &img_rect, window, &dest_rect);
		}
		void setPosition(Vector<int> new_pos) { position = new_pos; }
};

#endif
