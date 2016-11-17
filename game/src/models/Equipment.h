#ifndef EQUIPMENT_H

#include "Object.h"
#include "../utils/Vector.h"

#define EQUIPMENT_H

class Equipment : public Object{
	private:
		static const int DEFAULT_LIFE = 20;
		int life;
		Vector<int> position;
		int width;
		int height;
	public:
		Equipment(int x, int y, int w, int h) : position(Vector<int>(x, y)), width(w), height(h) { resetLife(); }
		void resetLife() { life = DEFAULT_LIFE; }
		int decreaseLife() { life--; return life; }
		Vector<int> getPosition() { return position; }
		int getWidth() { return width; }
		int getHeight() { return height; }
		Vector<int>* getAllApexes() {
			Vector<int>* list = new Vector<int>[4];
			list[0] = position;
			list[1] = position + Vector<int>(width, 0);
			list[2] = position + Vector<int>(0, height);
			list[3] = position + Vector<int>(width, height);
			return list;
		}
};

#endif
