#ifndef RUMBA_PANEL_H
#define RUMBA_PANEL_H

#include "Panel.hpp"

class RumbaPanel : public Panel {
	private:
		SDL_Rect prev_rect;
	public:
		RumbaPanel(Vector<int> initial_pos, char* img_path) : Panel(initial_pos, img_path) { }
		void setCenterPos(Vector<float> new_pos, int radius) { position = (Vector<int>)new_pos - radius; }
		SDL_Rect getPrevRect() { return prev_rect; }
		void drawPanel(SDL_Surface* window, int client_id) {
			Panel::drawPanel(window, client_id);
			prev_rect = dest_rect;
		}
};

#endif
