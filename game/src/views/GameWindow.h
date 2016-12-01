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
		LinkedList<RumbaPanel> rumba_list;
		LinkedList<EquipmentPanel> equip_panel_list;
		LinkedList<LifePanel> life_list;
		void drawObjects() {
			int i;
			rumba_list.resetCurrent();
			equip_panel_list.resetCurrent();
			life_list.resetCurrent();
			for(i = 0; i < rumba_list.getSize(); i++) rumba_list.get().drawPanel(window);
			for(i = 0; i < equip_panel_list.getSize(); i++) equip_panel_list.get().drawPanel(window);
			for(i = 0; i < life_list.getSize(); i++) life_list.get().drawPanel(window);
		}
	public:
		GameWindow(int h, int w, int num_of_player) : Window(h, w, GAME_WINDOW_BACKGROUND_PATH) {
			int i;
			rumba_list = LinkedList<RumbaPanel>();
			equip_panel_list = LinkedList<EquipmentPanel>();
			life_list = LinkedList<LifePanel>();
			for(i = 0; i < num_of_player; i++) rumba_list.add( RumbaPanel(i*100 + 50, i*100+50, CUSTOMIZED_ROOMBA_IMG_PATH) );
			rumba_list.add( RumbaPanel(GAME_WINDOW_WIDTH/2, GAME_WINDOW_HEIGHT/2, RUNAWAY_ROOMBA_IMG_PATH) );
		}
		void updateWindow() {
			drawBackground();
			drawObjects();
			SDL_Flip(window);
		}
		void updateObjects(RunawayRumba roomba, LinkedList<CustomizedRumba> c_rumba_list, LinkedList<Equipment> equip_list) {
			
		}
};

#endif
