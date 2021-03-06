#ifndef EQUIPMENT_PANEL_H
#define EQUIPMENT_PANEL_H

#include "../Setting.hpp"
#include "Panel.hpp"

class EquipmentPanel : public Panel {
	public:
		EquipmentPanel(int team_id)
			: Panel(
				Vector<int>( (team_id%2)*GAME_FIELD_WIDTH+(team_id%2)*(-EQUIPMENT_WIDTH), GAME_FIELD_HEIGHT/2 - EQUIPMENT_HEIGHT/2 ),
				(team_id%2 == 0) ? EQUIPMENT_LEFT_SIDE_IMG_PATH : EQUIPMENT_RIGHT_SIDE_IMG_PATH
			)  { }
};

#endif
