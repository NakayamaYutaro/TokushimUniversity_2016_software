#ifndef CUSTOMIZED_RUMBA_H

#include "Rumba.h"

#define CUSTOMIZED_RUMBA_H

class CustomizedRumba : public Rumba {
	private:
		Vector<float> speed_vec;
		Vector<float> prev_pos;
	public:
		CustomizedRumba(int x, int y, int r) : Rumba(x, y, r) {
			speed_vec = Vector<float>(0, 0);
			prev_pos = center_pos;
		}
		void controll(Vector<float> new_pos) {
			prev_pos = center_pos;
			center_pos = new_pos;
			speed_vec = center_pos - prev_pos;
		}
		Vector<float> getSpeedVector() {
			return (center_pos - prev_pos);
		}
};

#endif
