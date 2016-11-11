#ifndef RUNAWAY_RUMBA_H

#include "Rumba.h"
#include <stdarg.h>

#define RUNAWAY_RUMBA_H

class RunawayRumba : public Rumba {
	public:
		RunawayRumba(int x, int y, int w, int h) : position(Vector<int>(x, y)), width(w), height(h) {
			speed_vec = Vector<float>(0.0, 0.0);
		}
		void behave() { position = position + speed_vec; }
		void behaveCollision(int object_num, ...);
};

void RunawayRumba::behaveCollision(int object_num, ...) {
	va_list args;
	va_start(args, object_num);
	while(object_num > 0) {
		object_num = va_arg(args, Object);
		// judge and behave
	}
	va_end(args);
}

#endif
