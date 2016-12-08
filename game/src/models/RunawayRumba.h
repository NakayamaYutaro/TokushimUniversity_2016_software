#ifndef RUNAWAY_RUMBA_H
#define RUNAWAY_RUMBA_H

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <cmath>
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
	int i;
	for( i = 0; i < 4; i++) {

		// r.f. http://marupeke296.com/COL_2D_No5_PolygonToCircle.html
		Vector<int> S = list[(i+1)%4] - list[i];
		Vector<int> A = center_pos - list[i];
		Vector<int> B = center_pos - list[(i+1)%4];
		double distance = S.getOuterProduct(A)/S.getMagnitude();

		if( fabs(distance) < radius && (A.getInnerProduct(S)*B.getInnerProduct(S) < 0) ) {

			if( i%2 == 0 && (speed_vec.getY()*A.getY() < 0) ) {	// horizontal edge (hit edge is horizontal and roomba turns to the edge)
				equipment->decreaseLife();
				delete[] list;
				return Vector<float>( speed_vec.getX(), -speed_vec.getY() );
			}
			if( i%2 == 1 && (speed_vec.getX()*A.getX() < 0) ) {	// vertical edge
				equipment->decreaseLife();
				delete[] list;
				return Vector<float>( -speed_vec.getX(), speed_vec.getY() );
			}
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
	if( ( (field.w - (center_pos.getX() + radius)) < 0 && speed_vec.getX() > 0)
		|| (center_pos.getX() < radius && speed_vec.getX() < 0) ) {
		return Vector<float>( -speed_vec.getX(), speed_vec.getY() );
	}
	// judge horizontal side
	if( ((field.h - (center_pos.getY() + radius)) < 0 && speed_vec.getY() > 0)
		|| (center_pos.getY() < radius && speed_vec.getY() < 0) ) {
		return Vector<float>( speed_vec.getX(), -speed_vec.getY() );
	}
	return Vector<float>(0.0, 0.0);
}

void RunawayRumba::behave() { center_pos = center_pos + speed_vec; }

void RunawayRumba::behaveCollision(SDL_Rect field, LinkedList<Equipment>* equip_list, LinkedList<CustomizedRumba>* rumba_list) {
	Vector<float> tmp_vec = Vector<float>(0.0, 0.0);
	int i;

	tmp_vec += getReflectedVector(field);
	// reflected by all Equipments
	equip_list->resetCurrent();
	for(i = 0; i < equip_list->getSize(); i++) tmp_vec += getReflectedVector( equip_list->getPtr(i) );
	// reflected by all Customized roombas
	rumba_list->resetCurrent();
	for(i = 0; i < rumba_list->getSize(); i++) tmp_vec += getReflectedVector( rumba_list->getPtr(i) );
	// reflected by all field sides

	if(tmp_vec.getMagnitude() < 0.1) return;
	tmp_vec /= tmp_vec.getMagnitude();
	tmp_vec *= ROOMBA_SPEED;
	speed_vec = tmp_vec;
}

#endif
