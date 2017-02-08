#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "../utils/LinkedList.hpp"
#include "Window.hpp"
#include "RumbaPanel.hpp"
#include "EquipmentPanel.hpp"
#include "LifePanel.hpp"
#include "../Setting.hpp"
#include "../models/RunawayRumba.hpp"
#include "../models/CustomizedRumba.hpp"
#include "../models/Equipment.hpp"
#include <SDL/SDL_ttf.h>
#include <iostream>

using namespace std;

class GameWindow : public Window {
	private:
		vector<RumbaPanel> rumba_panel_list;
		vector<EquipmentPanel> equip_panel_list;
		vector<LifePanel> life_panel_list;
		SDL_Rect field_rect;
		TTF_Font* font;
		int client_id;
		void drawObjects();
		void initFont();
	public:
		GameWindow() : Window(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, (char*)GAME_WINDOW_BACKGROUND_PATH) { initFont(); }
		GameWindow(int client_id, int num_of_player, int team_num);
		~GameWindow() { TTF_CloseFont(font); }
		void updateWindow();
		void updateObjects(RunawayRumba roomba, vector<CustomizedRumba> c_rumba_list, vector<Equipment> equip_list);
		void drawBackground();
		SDL_Rect getFieldRect() { return field_rect; }
};

void GameWindow::updateWindow() {
	drawBackground();
	drawObjects();
	SDL_Flip(window);
}

void GameWindow::initFont() {
	font = TTF_OpenFont((const char*)FONT_PATH, 36);
	if(font == NULL) {
		cerr << TTF_GetError() << endl;
		exit(1);
	}
}

GameWindow::GameWindow(int id, int num_of_player, int team_num) : client_id(id), Window(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, (char*)GAME_WINDOW_BACKGROUND_PATH) {
	initFont();
	int i;
	rumba_panel_list = vector<RumbaPanel>();
	equip_panel_list = vector<EquipmentPanel>();
	life_panel_list = vector<LifePanel>();
	// push_back each roomba to lists
	for(i = 0; i < num_of_player; i++) rumba_panel_list.push_back( RumbaPanel(Vector<int>(i*100 + 50, i*100+50), (char*)CUSTOMIZED_ROOMBA_IMG_PATH) );
	rumba_panel_list.push_back( RumbaPanel(Vector<int>(GAME_WINDOW_WIDTH/2, GAME_WINDOW_HEIGHT/2), (char*)RUNAWAY_ROOMBA_IMG_PATH) );
	// push_back each equipment to list
	for(i = 0; i < team_num; i++) equip_panel_list.push_back( EquipmentPanel(i) );
	// push_back each life_panel to list
	for(i = 0; i < team_num; i++) life_panel_list.push_back( LifePanel(i) );

	field_rect.x = 0; field_rect.y = 0;
	field_rect.w = GAME_FIELD_WIDTH; field_rect.h = GAME_FIELD_HEIGHT;
}

void GameWindow::updateObjects(RunawayRumba roomba, vector<CustomizedRumba> c_rumba_list, vector<Equipment> equip_list) {
	unsigned int i;

	// -- update panel's postion -- //
	// for customized roomba
	CustomizedRumba tmp_roomba = CustomizedRumba(0,0);
	for(i = 0; i < c_rumba_list.size(); i++) {
		tmp_roomba = c_rumba_list[i];
		rumba_panel_list[i].setCenterPos( tmp_roomba.getCenterPos(), tmp_roomba.getRadius() );
	}
	// for runaway roomba
	rumba_panel_list[i].setCenterPos( roomba.getCenterPos(), roomba.getRadius() ) ;
	// -- update panel's postion -- //

	for(i = 0; i < equip_list.size(); i++) life_panel_list[i].setLife( equip_list[i].getLife() );
}

// --- private ---
void GameWindow::drawObjects() {
	unsigned int i;
	for(i = 0; i < equip_panel_list.size(); i++) equip_panel_list[i].drawPanel(window, client_id);
	for(i = 0; i < rumba_panel_list.size(); i++) rumba_panel_list[i].drawPanel(window, client_id);
	for(i = 0; i < life_panel_list.size(); i++) life_panel_list[i].drawPanel(window, font, client_id);
}

void GameWindow::drawBackground() {
	static bool is_initialized = false;
	SDL_Rect src_rect, dest_rect;
	if(!is_initialized) {
		Window::drawBackground();
		is_initialized = true;
		return;
	}
	// --- それぞれのルンバの描画範囲だけ背景を上塗り ---
	for(unsigned int i = 0; i < rumba_panel_list.size(); i++) {
		dest_rect = src_rect = rumba_panel_list[i].getPrevRect();
		SDL_BlitSurface(background, &src_rect, window, &dest_rect);
	}
}

#endif
