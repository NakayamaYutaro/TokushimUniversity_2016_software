#ifndef RUMBA_PANEL_H
#define RUMBA_PANEL_H

#include "Panel.hpp"

class RumbaPanel : public Panel {
	public:
		RumbaPanel(Vector<int> initial_pos, char* img_path) : Panel(initial_pos, img_path) { }
		void setCenterPos(Vector<float> new_pos, int radius) { position = (Vector<int>)new_pos - radius; }
};

#endif
