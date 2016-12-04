#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "../utils/LinkedList.h"
#include "Window.h"
#include "RumbaPanel.h"
#include "EquipmentPanel.h"
#include "LifePanel.h"
#include "../Setting.h"
#include "../models/RunawayRumba.h"
#include "../models/CustomizedRumba.h"
#include "../models/Equipment.h"

class GameWindow : public Window {
	private:
		LinkedList<RumbaPanel> rumba_panel_list;
		LinkedList<EquipmentPanel> equip_panel_list;
		LinkedList<LifePanel> life_panel_list;
		void drawObjects() {
			int i;
			rumba_panel_list.resetCurrent();
			equip_panel_list.resetCurrent();
			life_panel_list.resetCurrent();
			for(i = 0; i < rumba_panel_list.getSize(); i++) rumba_panel_list.get().drawPanel(window);
			for(i = 0; i < equip_panel_list.getSize(); i++) equip_panel_list.get().drawPanel(window);
			for(i = 0; i < life_panel_list.getSize(); i++) life_panel_list.get().drawPanel(window);
		}
	public:
		GameWindow() : Window(GAME_WINDOW_WIDTH, GAME_WINDOW_WIDTH, GAME_WINDOW_BACKGROUND_PATH) {}
		GameWindow(int num_of_player, int team_num) : Window(GAME_WINDOW_WIDTH, GAME_WINDOW_WIDTH, GAME_WINDOW_BACKGROUND_PATH) {
			int i;
			rumba_panel_list = LinkedList<RumbaPanel>();
			equip_panel_list = LinkedList<EquipmentPanel>();
			life_panel_list = LinkedList<LifePanel>();
			// add each roomba to lists
			for(i = 0; i < num_of_player; i++) rumba_panel_list.add( RumbaPanel(i*100 + 50, i*100+50, CUSTOMIZED_ROOMBA_IMG_PATH) );
			rumba_panel_list.add( RumbaPanel(GAME_WINDOW_WIDTH/2, GAME_WINDOW_HEIGHT/2, RUNAWAY_ROOMBA_IMG_PATH) );
			// add each equipment to list
			for(i = 0; i < team_num; i++) equip_panel_list.add( EquipmentPanel(i) );
			// add each life_panel to list
			for(i = 0; i < team_num; i++) life_panel_list.add( LifePanel(i) );
		}
		void updateWindow() {
			drawBackground();
			drawObjects();
			SDL_Flip(window);
		}
		void updateObjects(RunawayRumba *roomba, LinkedList<CustomizedRumba> *c_rumba_list, LinkedList<Equipment> *equip_list) {
			int i;

			// -- reset current pointer for iteration --//
			c_rumba_list->resetCurrent();
			equip_list->resetCurrent();
			rumba_panel_list.resetCurrent();
			life_panel_list.resetCurrent();
			// -- reset current pointer for iteration --//

			// -- update panel's postion -- //
			// for customized roomba
			CustomizedRumba tmp_roomba = CustomizedRumba(0,0);
			for(i = 0; i < c_rumba_list->getSize(); i++) {
				tmp_roomba = c_rumba_list->get();
				rumba_panel_list.getPtr()->setCenterPos( tmp_roomba.getCenterPos(), tmp_roomba.getRadius() );
			}
			// for runaway roomba
			rumba_panel_list.getPtr()->setCenterPos( roomba->getCenterPos(), roomba->getRadius() ) ;
			// -- update panel's postion -- //

			for(i = 0; i < equip_list->getSize(); i++) life_panel_list.getPtr()->setLife( equip_list->get().getLife() );
		}
};

#endif
