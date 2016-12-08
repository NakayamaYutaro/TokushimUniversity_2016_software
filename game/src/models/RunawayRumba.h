#ifndef RUNAWAY_RUMBA_H
#define RUNAWAY_RUMBA_H

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "Rumba.h"
#include "CustomizedRumba.h"
#include "Equipment.h"
#include "../utils/LinkedList.h"
#include "../Setting.h"

class RunawayRumba : public Rumba {
	private:
		bool judgeCollision(Equipment* equipment);
		bool judgeCollision(CustomizedRumba* rumba);
		Vector<float> speed_vec;
		Vector<float> getReflectedVector(Equipment* equipment);
		Vector<float> getReflectedVector(CustomizedRumba* rumba);
		Vector<float> getReflectedVector(SDL_Rect field);
	public:
		RunawayRumba(int x, int y) : Rumba(x, y) {
			speed_vec = Vector<float>(ROOMBA_SPEED*0.7, ROOMBA_SPEED*0.3);
		}
		void behave();
		void behaveCollision(SDL_Rect field, LinkedList<Equipment>* equip_list, LinkedList<CustomizedRumba>* rumba_list);
		Vector<float> getSpeedVec() { return speed_vec; }
};

Vector<float> RunawayRumba::getReflectedVector(Equipment* equipment) {
	Vector<int>* list = equipment->getAllApexes();
	Vector<int> tmp_vec;
	double vertical_len;
	int i;
	for( i = 0; i < 4; i++) {
		tmp_vec = list[(i+1)%4] - list[i];
		vertical_len = ( center_pos - (Vector<float>)list[i] ).getInnerProduct(tmp_vec) / pow(tmp_vec.getMagnitude(), 2.0);
		if( vertical_len < radius ) {
			equipment->decreaseLife();
			if(i%2 == 0) {	// vertical edge
				return Vector<float>( -speed_vec.getX(), speed_vec.getY() );
			} else {				// horizontal edge
				return Vector<float>( speed_vec.getX(), -speed_vec.getY() );
			}
			delete[] list;
		}
	}
	delete[] list;
	return Vector<float>(0,0);
}

Vector<float> RunawayRumba::getReflectedVector(CustomizedRumba* rumba) {
	Vector<float> tmp_vec = rumba->getCenterPos() - center_pos;
	if( tmp_vec.getMagnitude() < (rumba->getRadius() + radius)) {
		tmp_vec /= tmp_vec.getMagnitude();
		tmp_vec *= (-1 * rumba->getSpeedVector().getMagnitude());
		return tmp_vec;
	}
	return Vector<float>(0, 0);
}

Vector<float> RunawayRumba::getReflectedVector(SDL_Rect field) {
	// judge vertical side
	if( (field.w - (center_pos.getX() + radius)) < 0 || center_pos.getX() < radius ) return Vector<float>( -speed_vec.getX(), speed_vec.getY() );
	// judge horizontal side
	if( (field.w - (center_pos.getY() + radius)) < 0 || center_pos.getY() < radius ) return Vector<float>( speed_vec.getX(), -speed_vec.getY() );
	return Vector<float>(0.0, 0.0);
}

void RunawayRumba::behave() { center_pos = center_pos + speed_vec; }

void RunawayRumba::behaveCollision(SDL_Rect field, LinkedList<Equipment>* equip_list, LinkedList<CustomizedRumba>* rumba_list) {
	Vector<float> tmp_vec = Vector<float>(0.0, 0.0);
	int i;

	tmp_vec += getReflectedVector(field);
	// reflected by all Equipments
	equip_list->resetCurrent();
	for(i = 0; i < equip_list->getSize(); i++) tmp_vec += getReflectedVector( equip_list->getPtr() );
	// reflected by all Customized roombas
	rumba_list->resetCurrent();
	for(i = 0; i < rumba_list->getSize(); i++) tmp_vec += getReflectedVector( rumba_list->getPtr() );
	// reflected by all field sides

	if(tmp_vec.getMagnitude() > ROOMBA_SPEED) {
		tmp_vec /= tmp_vec.getMagnitude();
		tmp_vec *= ROOMBA_SPEED;
	}
	if(tmp_vec.getMagnitude() < 0.01) return;
	speed_vec = tmp_vec;
}

#endif
