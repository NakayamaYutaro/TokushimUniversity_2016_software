#ifdef CUSTOMIZED_RUMBA_H

#include "Rumba.h"

#define CUSTOMIZED_RUMBA_H

class CustomizedRumba : public Rumba {
	private:
		Vector<int> prev_pos;
	public:
		CustomizedRumba(int x, int y, int w, int h) : position(Vector<int>(x, y)), width(w), height(h) {
			speed_vec = Vector<float>(0.0, 0.0);
			prev_pos = position;
		}
		void controll(Vector<int> new_pos) {
			prev_pos = position;
			position = new_pos;
			speed_vec = position - prev_pos;
		}
};

#endif
