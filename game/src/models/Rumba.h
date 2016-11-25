#ifndef RUMBA_H

#include "Object.h"
#include "../utils/Vector.h"

#define RUMBA_H

class Rumba : public Object {
	protected:
		Vector<float> center_pos;
		int radius;
	public:
		Rumba(int x, int y, int r) : center_pos(Vector<float>(x, y)), radius(r) {}
		Vector<float> getCenterPos() { return center_pos; }
		int getRadius() { return radius; }
};

#endif
