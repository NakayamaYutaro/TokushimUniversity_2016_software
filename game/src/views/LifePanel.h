#ifndef LIFE_PANEL_H
#define LIFE_PANEL_H

#include "Panel.h"

class LifePanel : public Panel {
	private:
		int life;
	public:
		LifePanel(int team_id) :
			Panel(
				Vector<int>( (team_id%2)*GAME_FIELD_WIDTH+(team_id%2)*(-LIFE_PANEL_WIDTH), (team_id/2)*LIFE_PANEL_HEIGHT ) ,
				LIFE_PANEL_IMG_PATH
			), life(PLAYER_LIFE)  { }

		void setLife(int new_life) { life = new_life; }
};

#endif
