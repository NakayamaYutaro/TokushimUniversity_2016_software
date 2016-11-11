#ifndef EQUIPMENT_H

#include "Object.h"

#define EQUIPMENT_H

class Equipment : public Object{
	private:
		int life;
		static const DEFAULT_LIFE = 20;
	public:
		Equipment(int x, int y, int w, int h) : position(Vector<int>(x, y)), width(w), height(h) { resetLife(); }
		void resetLife() { life = DEFAULT_LIFE; }
		int decreaseLife() { life--; return life; }
};

#endif
