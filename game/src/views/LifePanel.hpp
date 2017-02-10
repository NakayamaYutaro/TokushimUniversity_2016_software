#ifndef LIFE_PANEL_H
#define LIFE_PANEL_H

#include "Panel.hpp"
#include "../Setting.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class LifePanel : public Panel {
	private:
		int life;
		SDL_Color white;
		SDL_Surface* text_img;
	public:
		LifePanel(int team_id) :
			Panel(
				Vector<int>( (team_id%2)*GAME_FIELD_WIDTH+(team_id%2)*(-LIFE_PANEL_WIDTH), (team_id/2)*LIFE_PANEL_HEIGHT ) ,
				LIFE_PANEL_IMG_PATH
			), life(DEFAULT_LIFE) {
				white.r = 255; white.g = 255; white.b = 255; 
				text_img = NULL;
			}

		void setLife(int new_life) { life = new_life; }

		void drawPanel(SDL_Surface* window, TTF_Font* font, bool is_server) {

			if(text_img != NULL) SDL_FreeSurface(text_img);

			Panel::drawPanel(window, is_server);

			std::ostringstream converter;
			converter << "life:" << life;

			text_img = TTF_RenderUTF8_Solid(font, converter.str().c_str(), white);
			if(text_img == NULL) {
				cerr << TTF_GetError() << endl;
				exit(1);
			}

			SDL_Rect src_rect = { 0, 0, static_cast<Uint16>(text_img->w), static_cast<Uint16>(text_img->h) };
			SDL_Rect dest_rect = {
				static_cast<Sint16>(position.getX()+30 - (is_server ? 0 : GAME_WINDOW_WIDTH) ),
				static_cast<Sint16>(position.getY()+50),
				static_cast<Uint16>(text_img->w),
				static_cast<Uint16>(text_img->h)
			};

			SDL_BlitSurface(text_img, &src_rect, window, &dest_rect);

		}

};

#endif
