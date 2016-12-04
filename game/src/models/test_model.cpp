#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <iostream>
#include "RunawayRumba.h"
#include "CustomizedRumba.h"
#include "../views/GameWindow.h"
#include "../Setting.h"
#include <time.h>
#include <sys/time.h>

int main(int argc, char** argv) {
	int i;
	struct timeval timeval[100];
	struct timespec request;

	LinkedList<CustomizedRumba>* c_rumbas = new LinkedList<CustomizedRumba>();
	LinkedList<Equipment> *equipments = new LinkedList<Equipment>();
	GameWindow window = GameWindow(2, 2);
	//RunawayRumba rumba = RunawayRumba( window.getWidth()/2 , window.getHeight()/2);
	RunawayRumba rumba = RunawayRumba( 200 , 100 );

	request.tv_sec = 0;
	request.tv_nsec = 10000000;

	SDL_Init(SDL_INIT_EVERYTHING);

	c_rumbas->add( CustomizedRumba( rumba.getCenterPos().getX() , rumba.getCenterPos().getY() + 40) );
	c_rumbas->add( CustomizedRumba( rumba.getCenterPos().getX() , rumba.getCenterPos().getY() - 40) );

	for(i = 0; i < 2; i++) equipments->add(Equipment(i));

	for(i = 0; i < 1000; i++) {
		rumba.behaveCollision(window.getRect(), equipments, c_rumbas);
		rumba.behave();
		window.updateObjects(&rumba, c_rumbas, equipments);
		window.updateWindow();
		gettimeofday(timeval + i, NULL);
		nanosleep(&request, NULL);
	}
	delete c_rumbas;

	return 0;
}
