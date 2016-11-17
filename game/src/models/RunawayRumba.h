#ifndef RUNAWAY_RUMBA_H

#include "Rumba.h"
#include "CustomizedRumba.h"
#include "Equipment.h"
#include "../views/GameWindow.h"
#include <stdarg.h>

#define RUNAWAY_RUMBA_H
#define MAX_SPEED 4.0

class RunawayRumba : public Rumba {
	private:
		bool judgeCollision(Equipment* equipment);
		bool judgeCollision(CustomizedRumba* rumba);
		Vector<double> speed_vec;
	public:
		RunawayRumba(int x, int y, int r) : Rumba(x, y, r) {
			speed_vec = Vector<double>(0.0, 0.0);
		}
		void behave();
		void behaveCollision(int object_num, ...);
		Vector<int> getReflectedVector(Equipment* equipment);
		Vector<int> getReflectedVector(CustomizedRumba* rumba);
};

Vector<int> RunawayRumba::getReflectedVector(Equipment* equipment) {
	Vector<int>* list = equipment->getAllApexes();
	Vector<int> tmp_vec;
	double vertical_len;
	int i;
	for( i = 0; i < 4; i++) {
		tmp_vec = list[(i+1)%4] - list[i];
		vertical_len = (center_pos - list[i]).getInnerProduct(tmp_vec) / pow(tmp_vec.getMagnitude(), 2.0);
		if( vertical_len < radius ) {
			equipment->decreaseLife();
			delete list;
			return ( (tmp_vec * vertical_len) + list[i]) - center_pos;
		}
	}
	delete list;
	return Vector<int>(0,0);
}

Vector<int> RunawayRumba::getReflectedVector(CustomizedRumba* rumba) {
	Vector<int> tmp_vec = rumba->getCenterPos() - center_pos;
	if( tmp_vec.getMagnitude() < (rumba->getRadius()) + radius) {
		tmp_vec /= tmp_vec.getMagnitude();
		tmp_vec *= (-1 * rumba->getSpeedVector().getMagnitude());
		return tmp_vec;
	}
	return Vector<int>(0, 0);
}

void RunawayRumba::behave() { center_pos = center_pos + speed_vec; }

void RunawayRumba::behaveCollision(GameWindow* field, int object_num, ...) {
	va_list args;
	Object obj;
	Equipment* equipment;
	CustomizedRumba* rumba;
	Vector<double> tmp_vec = speed_vec;
	int i;

	va_start(args, object_num);
	for(i = 0; i < object_num; i++) {
		equipment = NULL;
		rumba = NULL;

		obj = va_arg(args, Object);
		equipment = dynamic_cast<Equipment*>(&obj);
		if(equipment != NULL) tmp_vec += getReflectedVector(equipment);
		else {
			rumba = dynamic_cast<CustomizedRumba*>(&obj);
			if(rumba != NULL) tmp_vec += getReflectedVector(equipment);
		}
	}
	va_end(args);
	if(tmp_vec.getMagnitude() > MAX_SPEED) {
		tmp_vec /= vmp.getMagnitude();
		tmp_vec *= MAX_SPEED;
	}
	speed_vec = tmp_vec;
}

#endif
