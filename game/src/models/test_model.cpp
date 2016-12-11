#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <iostream>
#include "RunawayRumba.h"
#include "CustomizedRumba.h"
#include "../views/GameWindow.h"
#include "../Setting.h"
#include <time.h>
#include <sys/time.h>

#include "CppUTest/CommandLineTestRunner.h"

LinkedList<CustomizedRumba>* c_rumbas = new LinkedList<CustomizedRumba>();
LinkedList<Equipment> *equipments = new LinkedList<Equipment>();
//GameWindow window = GameWindow(2, 0);
GameWindow window = GameWindow(2, 2);
//RunawayRumba rumba = RunawayRumba( window.getWidth()/2 , window.getHeight()/2);
RunawayRumba rumba = RunawayRumba( 400 , 200 );

TEST_GROUP(ModelGroup) {
};
TEST(ModelGroup, ModelTest) {
	int i;
	bool is_finished = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_EVERYTHING);

	for(i = 0; i < 2; i++) equipments->add(Equipment(i));

	for(i = 0; !is_finished; i++) {

		if(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					is_finished = true;
					break;
			}
		}

		rumba.calcSpeedVector(window.getFieldRect(), equipments, c_rumbas);
		rumba.straight();

		window.updateObjects(&rumba, c_rumbas, equipments);
		window.updateWindow();

		SDL_Delay(16);
	}

	delete c_rumbas;
	delete equipments;

	SDL_Quit();

}

int main(int argc, char** argv) {
	c_rumbas->add( CustomizedRumba( rumba.getCenterPos().getX() , rumba.getCenterPos().getY() + 100) );
	c_rumbas->add( CustomizedRumba( rumba.getCenterPos().getX() + 180, rumba.getCenterPos().getY() - 180) );

	return CommandLineTestRunner::RunAllTests(argc, argv);
}
