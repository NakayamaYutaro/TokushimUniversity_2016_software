#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <iostream>
#include "CppUTest/CommandLineTestRunner.h"
#include "RunawayRumba.h"
#include "CustomizedRumba.h"
#include "../views/GameWindow.h"
#include "../Setting.h"
#include <time.h>
#include <sys/time.h>

LinkedList<CustomizedRumba>* c_rumbas = new LinkedList<CustomizedRumba>();
LinkedList<Equipment> *equipments = new LinkedList<Equipment>();
GameWindow window  = GameWindow(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, 2);
//RunawayRumba rumba = RunawayRumba( window.getWidth()/2 , window.getHeight()/2, 10);
RunawayRumba rumba = RunawayRumba( 0 , 0, 10);

TEST_GROUP(ModelGroup) {
};

TEST(ModelGroup, ModelTest) {
	int i;
	struct timeval timeval[100];
	struct timespec request;

	request.tv_sec = 0;
	request.tv_nsec = 100000000;

	//CHECK_EQUAL( 1, c_rumbas->getSize() );
	//CHECK_EQUAL( rumba.getCenterPos().getY() + 40, c_rumbas->get(0).getCenterPos().getY() );

	for(i = 0; i < 100; i++) {
		rumba.behaveCollision(window.getRect(), equipments, c_rumbas);
		rumba.behave();
		window.updateWindow();
		gettimeofday(timeval + i, NULL);
		nanosleep(&request, NULL);
	}

	CHECK_EQUAL( -1, rumba.getSpeedVec().getY()  );
	CHECK_EQUAL( 99, rumba.getCenterPos().getY() );

	delete c_rumbas;

}

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	c_rumbas->add( CustomizedRumba( rumba.getCenterPos().getX() , rumba.getCenterPos().getY() + 40, 10) );
	c_rumbas->add( CustomizedRumba( rumba.getCenterPos().getX() , rumba.getCenterPos().getY() - 40, 10) );
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
