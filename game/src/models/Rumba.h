#ifndef RUMBA_H

#include "../Setting.h"
#include "Object.h"
#include "../utils/Vector.h"

#define RUMBA_H

class Rumba : public Object {
	protected:
		Vector<float> center_pos;
		int radius;
	public:
		Rumba(int x, int y) : center_pos(Vector<float>(x, y) - ROOMBA_RADIUS), radius(ROOMBA_RADIUS) {}
		Vector<float> getCenterPos() { return center_pos; }
		void setCenterPos(Vector<int> vec) { center_pos = (Vector<float>)vec; }
		void setCenterPos(Vector<float> vec) { center_pos = vec; }
		int getRadius() { return radius; }
};

#endif
