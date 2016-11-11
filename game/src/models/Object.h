#ifndef OBJECT_H

#include "../utils/Vector.h"

#define OBJECT_H

class Object {
	private:
		Vector<int> position;
		int width, height;
	public:
		Object(int x, int y, int w, int h) : position(Vector<int>(x, y)), width(w), height(h) {}
		int getX() { return position.x; }
		int getY() { return position.y; }
		int getWidth() { return width; }
		int getHeight() { return height; }
};

#endif
