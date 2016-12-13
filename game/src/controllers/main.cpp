#include "../Setting.h"
#include "../utils/Timer.h"
#include "../models/RunawayRumba.h"
#include "../models/CustomizedRumba.h"
#include "../views/GameWindow.h"
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

using namespace std;

int main(int argc, char* argv[]) {

	int i;
	bool is_finished = false;
	bool is_server = false;
	string ip_address = "127.0.0.1";
	Timer timer = Timer();
	SDL_Event event;


	if(argc < 3) {		// validate arguments from console
		cerr << "Arguments is not enough!!" << endl;
		exit(1);
	}
	is_server = (argv[1][0] == 'S');

	// --- initialize each object --- //
	GameWindow window = GameWindow(2, 2);
	LinkedList<CustomizedRumba> c_rumbas = LinkedList<CustomizedRumba>();
	LinkedList<Equipment> equipments = LinkedList<Equipment>();
	RunawayRumba rumba = RunawayRumba( GAME_WINDOW_WIDTH/2 , GAME_WINDOW_HEIGHT/2);

	c_rumbas.add( CustomizedRumba( rumba.getCenterPos().getX() , rumba.getCenterPos().getY() + 100) );
	c_rumbas.add( CustomizedRumba( rumba.getCenterPos().getX() + 180, rumba.getCenterPos().getY() - 180) );
	for(i = 0; i < 2; i++) equipments.add(Equipment(i));
	// --- initialize each object --- //

	SDL_Init(SDL_INIT_EVERYTHING);

	while(!is_finished) {

		if(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:				// clicked quit buttom
					is_finished = true;
					break;
			}
		}

		// behave each object
		rumba.calcSpeedVector(window.getFieldRect(), &equipments, &c_rumbas);
		rumba.straight();

		// reflect to views
		window.updateObjects(&rumba, &c_rumbas, &equipments);
		window.updateWindow();

		timer.sleep();						// sleep for keep framerate constantly
	}

	return 0;
}
