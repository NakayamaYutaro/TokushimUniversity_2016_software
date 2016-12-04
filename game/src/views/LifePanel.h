#ifndef LIFE_PANEL_H
#define LIFE_PANEL_H

#include "Panel.h"

class LifePanel : public Panel {
	private:
		int life;
	public:
		LifePanel(int team_id) : life(PLAYER_LIFE), Panel((team_id%2)*EQUIPMENT_WIDTH, (team_id/2)*EQUIPMENT_HEIGHT, LIFE_PANEL_IMG_PATH) { }
		void setLife(int new_life) { life = new_life; }
};

#endif
